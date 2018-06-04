# include <SFML/Graphics.hpp>
# include "defs.h"
# include "field.h"
# include <iostream>

void draw_field(sf::RenderWindow &window, Field &field) {
    for (int i = 0; i < field.getHeight(); ++i) {
        for (int j = 0; j < field.getWidth(); ++j) {
            if (field[i][j] != 0) {
                sf::RectangleShape square(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                square.setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);
                switch(field[i][j]) {
                    case 1: square.setFillColor(sf::Color::Cyan); break;
                    case 2: square.setFillColor(sf::Color(0, 178, 178)); break;
                    case -1: square.setFillColor(sf::Color::Red); break;
                }
                window.draw(square);
            }
        }
    }
}

void key_pressed(sf::RenderWindow &window, Field &field, Direction &current_direction) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) current_direction = DOWN;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) current_direction = LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) current_direction = UP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) current_direction = RIGHT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) field.reset();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake");
    sf::Clock clock;

    Field field;
    Direction current_direction = RIGHT;

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) field.reseted = false;
        }

        key_pressed(window, field, current_direction);

        if (!field.reseted && clock.getElapsedTime().asMilliseconds() > SPEED) {
            field.refresh(current_direction);
            clock.restart();
        }

        window.clear(sf::Color::Black);
        draw_field(window, field);
        window.display();
    }
    return 0;
}
