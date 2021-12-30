#include <cmath>
#include <iostream>
#include <vector>

#include <raylib.h>
#include <raylib-cpp.hpp>

#include "Board.hpp"
#include "Vector2.hpp"

int screenWidth {800};
int screenHeight {450};

raylib::Color gridColor;
raylib::Color aliveCellColor;
raylib::Color deadCellColor;

float gridSize;
raylib::Vector2 gridVec;
raylib::Vector2 screenOffset;

std::vector<std::vector<uint8_t>> lifeBoard;

bool paused;

void InitGame();
void UpdateDraw(raylib::Window &window);
void Update(raylib::Window &window);
void Draw(raylib::Window &window);

int main() {
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    raylib::Window window(screenWidth, screenHeight, "Spiwocoal's raylib Practice - (Conway's Game of) Life");

    InitGame();

    SetTargetFPS(5);

    // Main game loop
    while (!window.ShouldClose()) {   // Detect window close button or ESC key
        UpdateDraw(window);
    }

    return 0;
}

void InitGame()
{
    gridColor = raylib::Color::DarkGray();
    gridSize = 20;
    gridVec = raylib::Vector2(gridSize, gridSize);

    aliveCellColor = raylib::Color::White();
    deadCellColor = raylib::Color::Black();

    paused = true;

    lifeBoard = Board::randomState(screenWidth / gridSize, screenHeight / gridSize);
    // lifeBoard = Board::deadState(screenWidth / gridSize, screenHeight / gridSize);
    // lifeBoard = Board::fromFile("life/toad.txt");

    for (auto &i : lifeBoard) {
        for (auto &j : i) {
            std::cout << j << " ";
        }

        std::cout << std::endl;
    }

    screenOffset = raylib::Vector2(std::fmod(screenWidth, gridSize), std::fmod(screenHeight, gridSize));
}

void UpdateDraw(raylib::Window &window)
{
    Update(window);
    Draw(window);
}

void Update(raylib::Window &window)
{
    if (IsKeyPressed(KEY_SPACE)) paused = !paused;
    if (paused)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            raylib::Vector2 mousePosition = GetMousePosition();
            mousePosition -= (screenOffset / 2.0f);

            raylib::Vector2 selectedCell = mousePosition / gridSize;
            lifeBoard.at(selectedCell.y).at(selectedCell.x) = !lifeBoard.at(selectedCell.y).at(selectedCell.x);
        }
    }

    if (!paused) lifeBoard = Board::nextState(lifeBoard, lifeBoard.size(), lifeBoard[0].size());
}

void Draw(raylib::Window &window)
{
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);

        for (size_t i {}; i < lifeBoard.size(); ++i) {
            for (size_t j {}; j < lifeBoard[i].size(); ++j) {
                if (lifeBoard[i][j] == 1) {
                    aliveCellColor.DrawRectangle(raylib::Vector2((j * gridSize) + (screenOffset.x / 2.0f),
                                                                 (i * gridSize) + (screenOffset.y / 2.0f)),
                                                 raylib::Vector2(20, 20));
                }
                else {
                    deadCellColor.DrawRectangle(raylib::Vector2((j * gridSize) + (screenOffset.x / 2.0f),
                                                                (i * gridSize) + (screenOffset.y / 2.0f)),
                                                raylib::Vector2(20, 20));
                }

                gridColor.DrawRectangleLines((j * gridSize) + (screenOffset.x / 2.0f),
                                             (i * gridSize) + (screenOffset.y / 2.0f),
                                             20, 20);
            }
        }
    }
    EndDrawing();
}
