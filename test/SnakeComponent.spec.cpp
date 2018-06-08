# include "catch.hpp"
# include "SnakeComponent.h"

using namespace std;

sf::Texture tileset;
SnakeSquareComponent square(0, 0, tileset, RIGHT);

SCENARIO("SnakeSquareComponent") {
    tileset.loadFromFile("../assets/textures/Snake.png");
    GIVEN("The snake's movement") {
        WHEN("It is moved to the right") {
            THEN("It should move to the right a distance equivalent to the time") {
                float prevY = square.getY();
                square.move(250);

                REQUIRE(square.getX() == Approx(SPEED * 250).margin(0.1));
                REQUIRE(square.getY() == Approx(prevY).margin(0.1));
            }
        }

        WHEN("It is moved up") {
            THEN("It should show up in the bottom of the screen") {
                float prevX = square.getX();
                float prevY = square.getY();
                square.direction = UP;
                square.move(250);

                REQUIRE(square.getX() == Approx(prevX).margin(0.1));
                REQUIRE(square.getY() == Approx(SCREEN_HEIGHT - (prevY + (SPEED * 250))).margin(0.1));
            }
        }

        WHEN("It's moved down") {
            THEN("It should get back to the top of the screen") {
                float prevX = square.getX();
                square.direction = DOWN;
                square.move(250);

                REQUIRE(square.getX() == Approx(prevX).margin(0.1));
                REQUIRE(square.getY() == Approx(0).margin(0.1));
            }
        }

        WHEN("It's moved left") {
            THEN("It should move to the left and get to its initial position") {
                square.direction = LEFT;
                square.move(250);

                REQUIRE(square.getX() == Approx(0).margin(0.1));
                REQUIRE(square.getY() == Approx(0).margin(0.1));
            }
        }
    }
}
