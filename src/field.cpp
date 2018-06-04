# include "field.h"
# include <random>
# include <iostream>

using namespace std;

Field::Field() {
    width = WIDTH / BLOCK_SIZE;
    height = HEIGHT / BLOCK_SIZE;
    snake = nullptr;
    reseted = true;

    matrix = new int*[height];
    int *p = new int[width*height];
    for (int i = 0; i < height; ++i) matrix[i] = p + (i * width);
    reset();
}

int* Field::operator [](int idx) { return matrix[idx]; }

void Field::spawnSnake() {
    for (auto &square : snake->getBody()) matrix[square.y][square.x] = 1;
    matrix[snake->getBody().back().y][snake->getBody().back().x] = 2;
}

Direction Field::refresh(Direction direction) {
    int prev_x = snake->getBody().back().x, prev_y = snake->getBody().back().y;
    int prev_tail_x = snake->getBody().front().x, prev_tail_y = snake->getBody().front().y;
    Direction prev_tail_direction = snake->getBody().front().direction;

    direction = snake->move(direction);
    matrix[prev_tail_y][prev_tail_x] = 0;
    int new_x = snake->getBody().back().x, new_y = snake->getBody().back().y;

    if (matrix[new_y][new_x] == -1) {
        snake->grow(prev_tail_x, prev_tail_y, prev_tail_direction);
        spawnFood();
    } else if (matrix[new_y][new_x] == 1) {
        cout << "You died. Looser.\n\n";
        reset();
        return RIGHT;
    }

    matrix[new_y][new_x] = 2;
    matrix[prev_y][prev_x] = 1;
    return direction;
}

void Field::spawnFood() {
    default_random_engine generator;
    generator.seed(random_device()());
    uniform_int_distribution<int> x_axis(0, width - 1);
    uniform_int_distribution<int> y_axis(0, height - 1);
    int food_x, food_y;

    do {
        food_x = x_axis(generator);
        food_y = y_axis(generator);
    } while (matrix[food_y][food_x] != 0);

    matrix[food_y][food_x] = -1;
}

void Field::reset() {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) matrix[i][j] = 0;
    delete snake;
    snake = new Snake(width, height);
    spawnSnake(); spawnFood();
    cout << "Field reseted.\n";
    reseted = true;
}

int Field::getWidth() { return width; }
int Field::getHeight() { return height; }
Field::~Field() { delete[] matrix; delete snake; }
