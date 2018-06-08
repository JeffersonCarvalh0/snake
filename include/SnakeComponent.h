# ifndef SNAKE_COMPONENT_H
# define SNAKE_COMPONENT_H

# include "defs.h"
# include <SFML/Graphics.hpp>
# include <list>

class SnakeSquareComponent {
private:
    float x, y;
    sf::Texture &tileset;
    sf::RectangleShape square;

public:
    Direction direction;

public:
    SnakeSquareComponent(float x, float y, sf::Texture &tileset, Direction direction);
    void setTextureRect(int x, int y);
    void move(float dt);
    float getX();
    float getY();
};

class SnakeComponent {
private:
    std::list<SnakeSquareComponent> body;
    sf::Texture *tileset;

public:
    SnakeComponent(sf::Texture &tileset, int initial_size = 5);
    void move(Direction direction, float dt);
    void grow();
    void refreshTiles();
    const std::list<SnakeSquareComponent>& getBody();
};

# endif /* end of include guard: SNAKE_COMPONENT_H */
