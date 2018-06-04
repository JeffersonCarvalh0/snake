# ifndef SNAKE_H
# define SNAKE_H

# include "defs.h"
# include <list>

struct SnakeSquare {
    int x, y;
    Direction direction;
    SnakeSquare(int x, int y, Direction direction);
};

class Snake {
private:
    int initial_size, field_width, field_height;
    std::list<SnakeSquare> body;

public:
    Snake(int field_width, int field_height, int initial_size = 5);
    const std::list<SnakeSquare>& getBody();
    void grow(int x, int y, Direction direction);
    Direction move(Direction new_direction);
};

# endif /* end of include guard: SNAKE_H */
