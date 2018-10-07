# include "SnakeComponent.h"
# include <iostream>

// SnakeSquareComponent

SnakeSquareComponent::SnakeSquareComponent(double x, double y, sf::Texture &tileset, Direction direction):
tileset(tileset), direction(direction) {
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

// SnakeComponent::SnakeComponent(st::Texture &tileset, int initial_size) {
//
// }
