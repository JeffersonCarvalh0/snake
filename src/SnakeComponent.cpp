# include "SnakeComponent.h"
# include <iostream>

// SnakeSquareComponent

SnakeSquareComponent::SnakeSquareComponent(double x, double y, sf::Texture &tileset, Direction direction):
x(x), y(y), tileset(tileset), direction(direction) {
    square.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    square.setTexture(&tileset);
    square.setPosition(x, y);
}

void SnakeSquareComponent::setTextureRect(int x, int y) {
    square.setTextureRect(sf::IntRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
}

void SnakeSquareComponent::move(double dt) {
    double offset = SPEED * dt;
    switch(direction) {
        case UP: square.move(0, -offset); break;
        case DOWN: square.move(0, offset); break;
        case LEFT: square.move(-offset, 0); break;
        case RIGHT: square.move(offset, 0); break;
    }

    if (getX() > WIDTH - BLOCK_SIZE) square.setPosition(getX() - WIDTH, getY());
    if (getX() < 0) square.setPosition(WIDTH + getX(), getY());
    if (getY() > HEIGHT - BLOCK_SIZE) square.setPosition(getX(), getY() - HEIGHT);
    if (getY() < 0) square.setPosition(getX(), HEIGHT + getY());
}

double SnakeSquareComponent::getX() { return square.getPosition().x; }
double SnakeSquareComponent::getY() { return square.getPosition().y; }

// SnakeComponent

// SnakeComponent::SnakeComponent(Snake *snake, sf::Texture *texture): snake(snake), texture(texture) {
//     auto snake_body = snake->getBody();
//     for (auto &square : snake_body) {
//         SnakeSquareComponent ssc(square.x, square.y, *texture, square.direction);
//         body.push_back(ssc);
//     }
//     refreshSprites();
// }
//
// void SnakeComponent::move(Direction direction, float dt) {
//     body.begin()->direction = direction;
//     for (auto &square : body) square.move(dt);
//     if ((int)body.back().getX() != snake->getBody().back().x || (int)body.back().getY() != snake->getBody().back().y) {
//         snake->move(direction);
//         if (snake->getBody().size() > body.size()) grow();
//     }
//
//     next(body.rbegin())->direction = body.rbegin()->direction;
//     refreshSprites();
// }
//
// void SnakeComponent::grow() {
//     auto square = snake->getBody().front();
//     body.push_front(SnakeSquareComponent(square.x, square.y, *texture, square.direction));
// }
//
// void SnakeComponent::refreshSprites() {
//     for (auto it = body.begin(); it != body.end(); ++it) {
//         if (it == body.begin()) {
//             switch(it->direction) {
//                 case UP: it->setTextureRect(2, 1); break;
//                 case DOWN: it->setTextureRect(0, 1); break;
//                 case LEFT: it->setTextureRect(3, 1); break;
//                 case RIGHT: it->setTextureRect(1, 1); break;
//             }
//         }
//
//         else if (it == prev(body.end())) {
//             switch(it->direction) {
//                 case UP: it->setTextureRect(2, 0); break;
//                 case DOWN: it->setTextureRect(0, 0); break;
//                 case LEFT: it->setTextureRect(3, 0); break;
//                 case RIGHT: it->setTextureRect(1, 0); break;
//             }
//         }
//
//         else if (it->direction != prev(it)->direction) {
//             if (it->direction == UP) {
//                 switch(prev(it)->direction) {
//                     case LEFT: it->setTextureRect(1, 2); break;
//                     case RIGHT: it->setTextureRect(2, 2); break;
//                     default: break;
//                 }
//             }
//
//             if (it->direction == DOWN) {
//                 switch(prev(it)->direction) {
//                     case LEFT: it->setTextureRect(0, 2); break;
//                     case RIGHT: it->setTextureRect(3, 2); break;
//                     default: break;
//                 }
//             }
//
//             if (it->direction == LEFT) {
//                 switch(prev(it)->direction) {
//                     case UP: it->setTextureRect(3, 2); break;
//                     case DOWN: it->setTextureRect(2, 2); break;
//                     default: break;
//                 }
//             }
//
//             if (it->direction == RIGHT) {
//                 switch(prev(it)->direction) {
//                     case UP: it->setTextureRect(0, 2); break;
//                     case DOWN: it->setTextureRect(1, 2); break;
//                     default: break;
//                 }
//             }
//         }
//
//         else {
//             switch(it->direction) {
//                 case UP:
//                 case DOWN: it->setTextureRect(0, 3); break;
//                 case LEFT:
//                 case RIGHT: it->setTextureRect(1, 3); break;
//             }
//         }
//     }
// }
//
// std::list<SnakeSquareComponent>& SnakeComponent::getBody() { return body; }
