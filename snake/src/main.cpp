#include <cstddef>
#include <cstdint>
#include <iostream>
#include <array>
#include <memory>

#include <raylib.h>
#include "Vector2.hpp"
#include "raylib-cpp.hpp"

const int screenWidth {800};
const int screenHeight {450};

const int maxSnake {255};
const int squareSize {30};

struct Snake
{
    raylib::Vector2 position;
    raylib::Vector2 speed;
    raylib::Vector2 size;
};

struct Food
{
    raylib::Vector2 position;
    raylib::Vector2 size;
    bool enabled;
};

std::array<Snake, maxSnake> snake {};
std::array<raylib::Vector2, maxSnake> snakePos {};
Food fruit {};

bool gameOver {};
bool paused {};

uint_fast64_t frameCounter {};
uint8_t tailCounter {2};

raylib::Vector2 scrOffset {};

void InitGame();
void UpdateDrawFrame();
void UpdateGame();
void DrawFrame();

int main(int argc, char *argv[])
{
    // <Initialization>
    raylib::Window window(screenWidth, screenHeight, "Spiwocoal's raylib Practice - Snake");
    InitGame();

    SetTargetFPS(60);
    // </Initialization>

    // <Main Game Loop>
    while (!window.ShouldClose()) {
        UpdateDrawFrame();
    }
    // </Main Game Loop

    return 0;
}

void InitGame()
{
    scrOffset = raylib::Vector2(screenWidth % squareSize, screenHeight % squareSize);

    for (auto &i : snake) {
       i.position = raylib::Vector2(scrOffset / 2);
       i.size = raylib::Vector2(squareSize, squareSize);
       i.speed = raylib::Vector2(squareSize, 0);
    }

    snake[0].position += snake[0].speed;

    for (auto &i : snakePos) {
       i = raylib::Vector2(0, 0);
    }

    gameOver = false;
    paused = false;

    fruit.size = raylib::Vector2(squareSize, squareSize);
    fruit.enabled = false;
}

void UpdateDrawFrame()
{
    UpdateGame();
    DrawFrame();
}

void UpdateGame()
{
    ++frameCounter;

    if (IsKeyPressed(KEY_UP) && snake[0].speed.y == 0) {
        snake[0].speed = raylib::Vector2(0, -squareSize);
    }
    if (IsKeyPressed(KEY_RIGHT) && snake[0].speed.x == 0) {
        snake[0].speed = raylib::Vector2(squareSize, 0);
    }
    if (IsKeyPressed(KEY_LEFT) && snake[0].speed.x == 0) {
        snake[0].speed = raylib::Vector2(-squareSize, 0);
    }
    if (IsKeyPressed(KEY_DOWN) && snake[0].speed.y == 0) {
        snake[0].speed = raylib::Vector2(0, squareSize);
    }
    if (IsKeyPressed(KEY_SPACE)) {
        for (size_t i {}; i <= tailCounter; ++i) {
            std::cout << "SNAKE " << i << ": " << snake[i].position.x << " " << snake[i].position.y << std::endl;
        }
        std::cout << "FRUIT: " << fruit.position.x << " " << fruit.position.y << std::endl;
    }

    for (size_t i {}; i <= tailCounter; ++i)
        snakePos[i] = snake[i].position;

    if (frameCounter % 10 == 0) {
        for (size_t i {tailCounter}; i > 0; --i) {
            snake[i].position = snakePos[i - 1];
        }

        snake[0].position += snake[0].speed;
    }

    if ((snake[0].position.x) >  (screenWidth - scrOffset.x)  ||
        (snake[0].position.x) <               0               ||
        (snake[0].position.y) > (screenHeight - scrOffset.y)  ||
        (snake[0].position.y) <               0               )
    {
        gameOver = true;
    }

    for (size_t i {1}; i <= tailCounter; ++i) {
        if (snake[i].position == snake[0].position) {
            gameOver = true;
        }
    }

    if (fruit.enabled == false) {
        fruit.enabled = true;
        fruit.position = raylib::Vector2(GetRandomValue(0, (screenWidth / squareSize) - 1) * squareSize + scrOffset.x / 2,
                                         GetRandomValue(0, (screenHeight / squareSize) - 1) * squareSize + scrOffset.y / 2);

        for (size_t i {}; i < tailCounter; ++i)
            while (snake[i].position == fruit.position) {
                fruit.position = raylib::Vector2(GetRandomValue(0, (screenWidth / squareSize) - 1) * squareSize + scrOffset.x / 2,
                                                 GetRandomValue(0, (screenHeight / squareSize) - 1) * squareSize + scrOffset.y / 2);
                i = 0;
            }
    }

    if (fruit.position == snake[0].position) {
        fruit.enabled = false;
        ++tailCounter;
        snake[tailCounter].position = snakePos[tailCounter - 1];
    }

    if (gameOver) std::cout << "Game Over" << std::endl;
}

void DrawFrame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (size_t i {}; i <= tailCounter; ++i) {
        DrawRectangleV(snake[i].position, snake[i].size, BLACK);
    }
    DrawRectangleV(fruit.position, fruit.size, GREEN);

    EndDrawing();
}
