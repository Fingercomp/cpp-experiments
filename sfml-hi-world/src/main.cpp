#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

sf::Sprite loadSprite(std::string filename) {
    static sf::Texture texture;
    texture.loadFromFile(filename);

    return sf::Sprite(texture);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Hi, world");
    window.setFramerateLimit(60);

    sf::Sprite ballSprite = loadSprite("resources/ball.png");
    ballSprite.setColor(sf::Color(255, 255, 255));
    ballSprite.setScale(sf::Vector2f(0.5f, 0.5f));
    ballSprite.setOrigin(sf::Vector2f(100, 100));
    ballSprite.move(sf::Vector2f(50, 50));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ballSprite.rotate(2.0f);
        window.clear(sf::Color::Black);
        window.draw(ballSprite);
        window.display();
    }

    return 0;
}
