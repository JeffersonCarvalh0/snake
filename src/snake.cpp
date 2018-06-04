# include "snake.h"
# include <iostream>

using namespace std;

SnakeSquare::SnakeSquare(int x, int y, Direction direction):
x(x), y(y), direction(direction) {}

Snake::Snake(int field_width, int field_height, int initial_size):
field_width(field_width), field_height(field_height) {
    for (int i = 0; i < initial_size; ++i)
        body.push_back(SnakeSquare(i, 0, RIGHT));
}

const list<SnakeSquare>& Snake::getBody() { return body; }

void Snake::grow(int x, int y, Direction direction) {
    SnakeSquare new_tail(x, y, direction);
    body.push_front(new_tail);
    cout << "Score: " << body.size() << '\n';
}

Direction Snake::move(Direction new_direction) {
    SnakeSquare head = body.back();

    switch(new_direction) {
        case UP: if (head.direction == DOWN) new_direction = DOWN; break;
        case DOWN: if (head.direction == UP) new_direction = UP; break;
        case LEFT: if (head.direction == RIGHT) new_direction = RIGHT; break;
        case RIGHT: if (head.direction == LEFT) new_direction = LEFT; break;
    }

    SnakeSquare new_head(head.x, head.y, new_direction);

    switch(new_direction) {
        case UP: new_head.y = (new_head.y + 1) % field_height; break;
        case DOWN: if (--new_head.y < 0) new_head.y += field_height;  break;
        case LEFT: if (--new_head.x < 0) new_head.x += field_width; break;
        case RIGHT: new_head.x = (new_head.x + 1) % field_width; break;
    }
    body.push_back(new_head);
    body.pop_front();
    for (auto it = body.begin(); next(it) != body.end(); ++it) it->direction = next(it)->direction;
    return new_direction;
}
