#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace Board
{
    std::vector<std::vector<uint8_t>> deadState(const uint8_t width, const uint8_t height);
    std::vector<std::vector<uint8_t>> randomState(const uint8_t width, const uint8_t height);
    std::vector<std::vector<uint8_t>> fromFile(const std::string &filePath);

    bool writeToFile(const std::string &filePath);

    std::vector<std::vector<uint8_t>> nextState(const std::vector<std::vector<uint8_t>> &prevState,
                                                const uint8_t width, const uint8_t height);
    uint8_t getAliveNeighbors(const std::vector<std::vector<uint8_t>> &board,
                              const uint8_t width, const uint8_t height,
                              const uint8_t i, const uint8_t j);

    std::string serialize(const std::vector<std::vector<uint8_t>> &board,
                          const uint8_t width, const uint8_t height);
};
