#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const int BLOCK_SIZE = 20;

struct SnakeSegment {
    int x, y;
};

struct Obstacle {
    int x, y;
};

void showGameOverMessage(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font!" << std::endl;
        return;
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over! You hit an obstacle.");
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(WIDTH / 2 - 200, HEIGHT / 2 - 20);

    window.clear();
    window.draw(gameOverText);
    window.display();

    sf::sleep(sf::seconds(3));
}

bool isCollision(const std::vector<SnakeSegment>& snake, const Obstacle& obstacle) {
    for (const auto& segment : snake) {
        if (segment.x == obstacle.x && segment.y == obstacle.y) {
            return true;
        }
    }
    return false;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake Game");
    window.setVerticalSyncEnabled(false);

    std::vector<SnakeSegment> snake = { {WIDTH / 2, HEIGHT / 2} };
    int directionX = BLOCK_SIZE, directionY = 0;

    std::vector<Obstacle> obstacles;
    int obstacleTimer = 0;
    const int OBSTACLE_SPAWN_TIME = 50;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && directionX == 0) {
            directionX = -BLOCK_SIZE; directionY = 0;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && directionX == 0) {
            directionX = BLOCK_SIZE; directionY = 0;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && directionY == 0) {
            directionX = 0; directionY = -BLOCK_SIZE;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && directionY == 0) {
            directionX = 0; directionY = BLOCK_SIZE;
        }

        SnakeSegment newHead = { snake[0].x + directionX, snake[0].y + directionY };

        if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT) {
            showGameOverMessage(window);
            window.close();
        }

        for (const auto& segment : snake) {
            if (segment.x == newHead.x && segment.y == newHead.y) {
                showGameOverMessage(window);
                window.close();
            }
        }

        bool hitObstacle = false;
        for (const auto& obstacle : obstacles) {
            if (obstacle.x == newHead.x && obstacle.y == newHead.y) {
                hitObstacle = true;
                break;
            }
        }

        if (hitObstacle) {
            showGameOverMessage(window);
            window.close();
        }

        snake.insert(snake.begin(), newHead);
        snake.pop_back();

        obstacleTimer++;
        if (obstacleTimer >= OBSTACLE_SPAWN_TIME) {
            obstacleTimer = 0;
            Obstacle newObstacle = { rand() % (WIDTH / BLOCK_SIZE) * BLOCK_SIZE, rand() % (HEIGHT / BLOCK_SIZE) * BLOCK_SIZE };

            while (isCollision(snake, newObstacle)) {
                newObstacle = { rand() % (WIDTH / BLOCK_SIZE) * BLOCK_SIZE, rand() % (HEIGHT / BLOCK_SIZE) * BLOCK_SIZE };
            }

            obstacles.push_back(newObstacle);
        }

        window.clear();

        for (const auto& segment : snake) {
            sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            block.setPosition(segment.x, segment.y);
            block.setFillColor(sf::Color::Green);
            window.draw(block);
        }

        for (const auto& obstacle : obstacles) {
            sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            block.setPosition(obstacle.x, obstacle.y);
            block.setFillColor(sf::Color::Red);
            window.draw(block);
        }

        window.display();
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}
