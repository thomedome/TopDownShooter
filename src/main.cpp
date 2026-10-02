#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

float floatClamp(const float d, const float min, const float max) { // Thank you random man on stack overflow!
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

class Player {

    int health {100};
    float moveSpeed {250.f};

public:
    sf::Vector2f position; // X, Y
    sf::View playerView{position, {750, 750}};

    sf::RectangleShape objOnScreen {sf::Vector2f(50, 50)};

    Player() {
        position = sf::Vector2f(1500, 1500);
        objOnScreen.setOrigin(objOnScreen.getLocalBounds().getCenter());
    }

    void update(const float dt) {

        using namespace sf::Keyboard;

        if (isKeyPressed(Key::D)) {
            position.x += (moveSpeed * dt);
        }

        if (isKeyPressed(Key::A)) {
            position.x -= (moveSpeed * dt);
        }

        if (isKeyPressed(Key::S)) {
            position.y += (moveSpeed * dt);
        }

        if (isKeyPressed(Key::W)) {
            position.y -= (moveSpeed * dt);
        }

        position.x = floatClamp(position.x, objOnScreen.getSize().x / 2, 3000 - objOnScreen.getSize().x / 2);
        position.y = floatClamp(position.y, objOnScreen.getSize().y / 2, 3000 - objOnScreen.getSize().y / 2);

        objOnScreen.setPosition(position);

        // Need to Clamp playerView to map.

        const sf::Vector2f camSize = playerView.getSize();

        const float camX = floatClamp(position.x, camSize.x / 2, 3000 - camSize.x);
        const float camY = floatClamp(position.y, camSize.y / 2, 3000 - camSize.y);

        const sf::Vector2f camView {camX, camY};

        playerView.setCenter(camView); // Set View to Player Pos
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(objOnScreen);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Top Down Shooter");

    const sf::Texture mapTexture {"assets/testMap.jpg"};
    const sf::Sprite mapSprite(mapTexture);

    sf::Clock dtClock;

    const auto onClose = [&window](const sf::Event::Closed&)
    {
        window.close();
        exit(0);
    };

    const auto onKeyPressed = [&window](const sf::Event::KeyPressed& keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Escape) {
            window.close();
            exit(0);
        }
    };


    Player player;

    window.setVerticalSyncEnabled(true); // VSync

    while (window.isOpen()) {

        const float dt = dtClock.restart().asSeconds();

        window.handleEvents(onClose, onKeyPressed); // One Off Keycodes

        window.setView(player.playerView);
        window.clear(sf::Color::Black);
        window.draw(mapSprite); // Draw the map

        player.update(dt);
        player.draw(window); // Draw the player

        window.display();
    }
    return 0;
}