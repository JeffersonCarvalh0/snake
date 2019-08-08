# ifndef FIELD_H
# define FIELD_H

# include <SFML/Audio.hpp>

# include "defs.h"
# include "snake.h"
# include <list>

class Field {
private:
    int width, height, **matrix;
    sf::SoundBuffer looseBuffer;
    sf::Sound looseSound;
    Snake *snake;

public:
    bool reseted;
    Field();
    int* operator [](int idx);
    void spawnSnake();
    Direction refresh(Direction direction);
    void spawnFood();
    void reset();
    const std::list<SnakeSquare> &getSnakeBody();
    int getScore();
    int getWidth();
    int getHeight();
    ~Field();
};

# endif /* end of include guard: FIELD_H */
