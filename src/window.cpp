# include <SFML/Graphics.hpp>
# include "defs.h"
# include "field.h"
# include <string>
# include <iostream>

class Window {
public:
    sf::RenderWindow window;
    sf::Clock clock;

    sf::Font roboto;
    sf::Texture tileset;

    Field field;
    Direction current_direction;

    double offset;

    Window() {
        window.create(sf::VideoMode(WIDTH, HEIGHT), "Snake");
        roboto.loadFromFile("../assets/fonts/RobotoMono-Bold.ttf");
        tileset.loadFromFile("../assets/textures/Snake.png");
        current_direction = RIGHT;
        offset = 0.0;

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

            if (!field.reseted) {
                offset += SPEED * clock.getElapsedTime().asMilliseconds();
                update(); clock.restart();
            }
            update();
        }
    }

    void update() {
        window.clear(sf::Color::Black);
        drawField();
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
        auto body = field.getSnakeBody();
        for (auto it = body.begin(); it != body.end(); ++it) {
            sf::RectangleShape body_part(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            body_part.setPosition(it->x * BLOCK_SIZE, it->y * BLOCK_SIZE);
            body_part.setTexture(&tileset);

            if (it->direction == UP || it->direction == DOWN)
                body_part.move(0, offset);
            else if (it->direction == LEFT || it->direction == RIGHT)
                body_part.move(offset, 0);

            if (it == body.begin()) {
                switch(it->direction) {
                    case UP: body_part.setTextureRect(sf::IntRect(2 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                    case DOWN: body_part.setTextureRect(sf::IntRect(0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                    case LEFT: body_part.setTextureRect(sf::IntRect(3 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                    case RIGHT: body_part.setTextureRect(sf::IntRect(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                }
            }

            else if (it == prev(body.end())) {
                switch(it->direction) {
                    case UP: body_part.setTextureRect(sf::IntRect(2 * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE)); break;
                    case DOWN: body_part.setTextureRect(sf::IntRect(0, 0, BLOCK_SIZE, BLOCK_SIZE)); break;
                    case LEFT: body_part.setTextureRect(sf::IntRect(3 * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE)); break;
                    case RIGHT: body_part.setTextureRect(sf::IntRect(BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE)); break;
                }
            }

            else if (it->direction != prev(it)->direction) {
                if (it->direction == UP) {
                    switch(prev(it)->direction) {
                        case LEFT: body_part.setTextureRect(sf::IntRect(BLOCK_SIZE, 2 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                        case RIGHT: body_part.setTextureRect(sf::IntRect(2 * BLOCK_SIZE, 2 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                        default: break;
                    }
                }

                if (it->direction == DOWN) {
                    switch(prev(it)->direction) {
                        case LEFT: body_part.setTextureRect(sf::IntRect(0, 2 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                        case RIGHT: body_part.setTextureRect(sf::IntRect(3 * BLOCK_SIZE, 2 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                        default: break;
                    }
                }

                if (it->direction == LEFT) {
                    switch(prev(it)->direction) {
                        case UP: body_part.setTextureRect(sf::IntRect(3 * BLOCK_SIZE, 2 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                        case DOWN: body_part.setTextureRect(sf::IntRect(2 * BLOCK_SIZE, 2 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                        default: break;
                    }
                }

                if (it->direction == RIGHT) {
                    switch(prev(it)->direction) {
                        case UP: body_part.setTextureRect(sf::IntRect(0, 2 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                        case DOWN: body_part.setTextureRect(sf::IntRect(BLOCK_SIZE, 2 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                        default: break;
                    }
                }
            }

            else {
                switch(it->direction) {
                    case UP:
                    case DOWN: body_part.setTextureRect(sf::IntRect(0, 3 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                    case LEFT:
                    case RIGHT: body_part.setTextureRect(sf::IntRect(BLOCK_SIZE, 3 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); break;
                }
            }
            window.draw(body_part);
        }

        if (body.back().x + offset >= body.back().x + 1 || body.back().y + offset >= body.back().y + 1) {
            field.refresh(current_direction); offset = 0.0;
        }
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
