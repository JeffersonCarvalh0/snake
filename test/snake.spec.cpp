# include "catch.hpp"
# include "snake.h"
# include "defs.h"

using namespace std;

int field_width = WIDTH/BLOCK_SIZE;
int field_height = HEIGHT/BLOCK_SIZE;

Snake snake(field_width, field_height);
const list<SnakeSquare>& snakeBody = snake.getBody();

SCENARIO("Snake") {
    GIVEN("A snake object") {
        WHEN("The snake moves to the right") {
            snake.move(RIGHT);

            THEN("Its body should have the proper coordinates") {
                int i = 1; for (auto &square : snakeBody) {
                    REQUIRE(square.x == i);
                    REQUIRE(square.y == 0);
                    ++i;
                }
            }
        }

        WHEN("The snake eats something") {
            snake.grow(0, 0, RIGHT);

            THEN("Its body should get bigger") {
                REQUIRE(snakeBody.size() == 6);
            }

            THEN("Its new tail should be in the right coordinates") {
                REQUIRE(snakeBody.front().x == 0);
                REQUIRE(snakeBody.front().y == 0);
            }
        }

        WHEN("The snake moves down at the bottom line") {
            snake.move(DOWN);

            THEN("Its head should be in the top") {
                REQUIRE(snakeBody.back().y == field_height - 1);
                REQUIRE(snakeBody.back().x == 5);
            }

            THEN("The rest of its body should sill be in the bottom") {
                int i = 1; for (auto &square : snakeBody) {
                    if (i == 4) break;
                    REQUIRE(square.y == 0);
                    REQUIRE(square.x == i);
                    ++i;
                }
            }
        }
    }
}
