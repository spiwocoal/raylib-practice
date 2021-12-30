#include "Board.hpp"

#include <cstdint>
#include <fstream>
#include <random>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

namespace Board {
    std::vector<std::vector<uint8_t>> deadState(const uint8_t width, const uint8_t height)
    {
        return std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(width, false));
    }

    std::vector<std::vector<uint8_t>> randomState(const uint8_t width, const uint8_t height)
    {
        std::vector<std::vector<uint8_t>> board(height, std::vector<uint8_t>(width, false));

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);

        for (auto &row : board) {
            for (auto &col : row) {
                col = dis(gen);
            }
        }

        return board;
    }

    std::vector<std::vector<uint8_t>> fromFile(const std::string &filePath)
    {
        std::vector<std::vector<uint8_t>> board;
        uint8_t index {};

        std::ifstream inputFile;
        inputFile.open(filePath);
        std::string line;

        while (inputFile) {
            board.push_back(std::vector<uint8_t>());
            std::getline(inputFile, line);

            for (const auto &i : line) {
                if (i == '1') board.at(index).push_back(1);
                else board.at(index).push_back(0);
            }
            index++;
        }

        board.pop_back();

        return board;
    }

    bool writeToFile(const std::string &filePath)
    {
        // TODO
        return true;
    }

    std::string serialize(const std::vector<std::vector<uint8_t>> &board,
                          const uint8_t width, const uint8_t height)
    {
        std::stringstream stream;

        stream << std::string(width + 2, '_');
        stream << '\n';
        for (const auto &row : board) {
            stream << '|';
            for (const auto &i : row) {
                if (i) stream << '#';
                else stream << '_';
            }

            stream << '|' << '\n';
        }
        stream << std::string(width + 2, '-');
        stream << '\n';

        return stream.str();
    }

    std::vector<std::vector<uint8_t>> nextState(const std::vector<std::vector<uint8_t>> &currState,
                                                uint8_t width, uint8_t height)
    {
        std::vector<std::vector<uint8_t>> newState = currState;

        for (uint8_t i {}; i < width; ++i) {
            for (uint8_t j {}; j < height; ++j) {
                bool currCellState = currState.at(i).at(j);
                uint8_t aliveNeighbors = getAliveNeighbors(currState, width, height, i, j);

                if (currCellState && (aliveNeighbors < 2 || aliveNeighbors > 3))
                    newState.at(i).at(j) = false;
                else if (!currCellState && aliveNeighbors == 3) newState.at(i).at(j) = true;
            }
        }

        return newState;
    }

    uint8_t getAliveNeighbors(const std::vector<std::vector<uint8_t>> &board,
                              const uint8_t width, const uint8_t height,
                              const uint8_t i, const uint8_t j)
    {
        uint8_t count = 0;

        if (i > 0) {
            if (j > 0) {
                if (board.at(i - 1).at(j - 1) == 1) ++count;
            }

            if (j < height - 1) {
                if (board.at(i - 1).at(j + 1) == 1) ++count;
            }

            if (board.at(i - 1).at(j) == 1) ++count;
        }

        if (j > 0) {
            if (i < width - 1) {
                if (board.at(i + 1).at(j - 1) == 1) ++count;
            }

            if (board.at(i).at(j - 1) == 1) ++count;
        }

        if (j < height - 1) {
            if (i < width - 1) {
                if (board.at(i + 1).at(j + 1) == 1) ++count;
            }

            if (board.at(i).at(j + 1) == 1) ++count;
        }

        if (i < width - 1) {
            if (board.at(i + 1).at(j) == 1) ++count;
        }

        return count;
    }
}
