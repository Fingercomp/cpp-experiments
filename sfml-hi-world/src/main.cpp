#include <iostream>
#include <string>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

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
    // Set up Box2D world
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world {gravity};

    // Settings
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Hi, world");
    window.setFramerateLimit(60);

    // Create a "ground"
    b2BodyDef bodyGroundDef;
    bodyGroundDef.type = b2_dynamicBody;
    bodyGroundDef.position.Set(0.0f, -10.0f);
    b2Body *bodyGround = world.CreateBody(&bodyGroundDef);

    b2PolygonShape boxGround;
    boxGround.SetAsBox(50.0f, 10.0f);

    bodyGround->CreateFixture(&boxGround, 0.0f);

    // Create a ball tile
    b2BodyDef bodyBallDef;
    bodyBallDef.type = b2_dynamicBody;
    bodyBallDef.position.Set(50.0f, 50.0f);
    b2Body *bodyBall = world.CreateBody(&bodyBallDef);

    b2PolygonShape dynamicBoxBall;
    dynamicBoxBall.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDefBall;
    fixtureDefBall.shape = &dynamicBoxBall;
    fixtureDefBall.density = 1.0f;
    fixtureDefBall.friction = 0.1f;

    bodyBall->CreateFixture(&fixtureDefBall);

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
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized: {
                    sf::FloatRect visibleArea{0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height)};
                    window.setView(sf::View(visibleArea));
                    break;
                }
                default:
                    break;
            }
        }
        // Update the world
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 ballPosition = bodyBall->GetPosition();
        float32 ballAngle = bodyBall->GetAngle();

        // Update the tiles
        ballSprite.setPosition(ballPosition.x, ballPosition.y + 100);

        window.clear(sf::Color::White);
        window.draw(ballSprite);
        window.draw(text);
        window.display();
    }

    return 0;
}
