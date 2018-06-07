# include <SFML/Graphics.hpp>
# include "defs.h"
# include "field.h"
# include "SnakeComponent.h"
# include <iostream>
# include <list>

class Window {
public:
    sf::RenderWindow window;
    sf::Clock clock;

    sf::Font roboto;
    sf::Texture tileset;

    SnakeComponent snake;
    Field field;
    Direction current_direction;

    Window() {
        window.create(sf::VideoMode(WIDTH, HEIGHT), "Snake");
        roboto.loadFromFile("../assets/fonts/RobotoMono-Bold.ttf");
        tileset.loadFromFile("../assets/textures/Snake.png");
        current_direction = RIGHT;
        snake = SnakeComponent(field.snake, &tileset);

        while(window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (event.type == sf::Event::KeyPressed && field.reseted) {
                    keyPressed();
                    field.refresh(current_direction);
                    clock.restart();
                }
            }

            keyPressed();

            if (!field.reseted) { update(clock.getElapsedTime()); clock.restart(); }
            update(clock.getElapsedTime());
        }
    }

    void update(sf::Time dt) {
        window.clear(sf::Color::Black);
        drawField();
        snake.move(current_direction, dt.asMilliseconds());
        drawSnake();
        drawHud();
        window.display();
    }

    void keyPressed() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) current_direction = DOWN;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) current_direction = LEFT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) current_direction = UP;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) current_direction = RIGHT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) field.reset();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
    }

    void drawSnake() {
        for (auto &body_part : snake.getBody()) window.draw(body_part.square);
    }

    void drawField() {
        for (int i = 0; i < field.getHeight(); ++i) {
            for (int j = 0; j < field.getWidth(); ++j) {
                sf::RectangleShape square(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                square.setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);
                square.setTexture(&tileset);
                square.setTextureRect(sf::IntRect(BLOCK_SIZE * 3, BLOCK_SIZE * 3, BLOCK_SIZE, BLOCK_SIZE));
                window.draw(square);

                if (field[i][j] == -1) {
                    square.setTextureRect(sf::IntRect(BLOCK_SIZE * 2, BLOCK_SIZE * 3, BLOCK_SIZE, BLOCK_SIZE));
                    window.draw(square);
                }
            }
        }
    }

    void drawHud() {
        sf::Text score;
        score.setFont(roboto);
        score.setFillColor(sf::Color(255, 255, 255, 150));
        score.setCharacterSize(24);
        score.setPosition(10, 10);
        score.setString("score: " + std::to_string(field.getScore()));
        window.draw(score);
    }
};

int main() {
    Window window;
    return 0;
}
