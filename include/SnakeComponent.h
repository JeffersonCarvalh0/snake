# ifndef SNAKE_COMPONENT_H
# define SNAKE_COMPONENT_H

# include "defs.h"
# include "snake.h"
# include <SFML/Graphics.hpp>
# include <list>

class SnakeSquareComponent {
private:
    sf::Texture &texture;
    float x, y;

public:
    sf::RectangleShape square;
    Direction direction;

public:
    SnakeSquareComponent(float x, float y, sf::Texture &texture, Direction direction);
    void setTextureRect(int idx_x, int idx_y);
    void move(float dt);
    float getX();
    float getY();
};

class SnakeComponent {
private:
    std::list<SnakeSquareComponent> body;
    Snake *snake;
    sf::Texture *texture;

public:
    SnakeComponent(Snake *snake = nullptr, sf::Texture *texture = nullptr);
    void move(Direction direction, float dt);
    void grow();
    void refreshSprites();
    std::list<SnakeSquareComponent>& getBody();
};

# endif /* end of include guard: SNAKE_COMPONENT_H */
