#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "cmake_options.hpp"

sf::Sprite loadSprite(std::string name) {
    static sf::Texture texture;
    if (!texture.loadFromFile(RESOURCES_DIR + static_cast<std::string>("/textures/") + name)) {
        std::cerr << "Could not load the texture: " + name << "\n";
    }

    texture.setSmooth(true);

    return sf::Sprite(texture);
}

sf::Font loadFont(std::string name) {
    sf::Font font;
    if (!font.loadFromFile(RESOURCES_DIR + static_cast<std::string>("/fonts/") + name)) {
        std::cerr << "Could not load the font: " + name << "\n";
    }

    return font;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hi, world");
    window.setFramerateLimit(60);

    sf::Sprite ballSprite = loadSprite("ball.png");
    ballSprite.setColor(sf::Color(255, 255, 255));
    ballSprite.setScale(sf::Vector2f(0.5f, 0.5f));
    ballSprite.setOrigin(sf::Vector2f(100, 100));
    ballSprite.move(sf::Vector2f(50, 50));

    sf::Font font = loadFont("Anonymous Pro Minus.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setColor(sf::Color(0x20, 0xaf, 0xff));
    text.setPosition(sf::Vector2f(150, 25));
    text.setString("Hello, world!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ballSprite.rotate(2.0f);
        window.clear(sf::Color::White);
        window.draw(ballSprite);
        window.draw(text);
        window.display();
    }

    return 0;
}
