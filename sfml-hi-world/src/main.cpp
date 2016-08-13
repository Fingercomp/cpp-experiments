#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Hi, world");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        window.draw(shape);
        window.display();
    }

    return 0;
}
