#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>

float floatClamp(const float d, const float min, const float max) { // Thank you random man on stack overflow!
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

class Player;

class Weapon {
    public:
        int damage {};
        int TTL {};

        Player& Parent;
        const std::string name {};

        sf::RectangleShape objectOnScreen{{25, 10}};

        explicit Weapon(Player& owner) : Parent(owner) {
            objectOnScreen.setFillColor(sf::Color::Black);
            objectOnScreen.setOrigin({-10.f, objectOnScreen.getSize().y / 2}); // This is a test weapon for now... unless i want to make cube warfare ;p
        }

        void lookAtMouse(sf::Vector2f mousePosition);

        void update(sf::Vector2f mousePosition);

        void draw(sf::RenderWindow& window) const {
            window.draw(objectOnScreen);
        }
};

class Player {

    int health {100};
    float moveSpeed {250.f};

public:
    Weapon heldWeapon;

    sf::Vector2f mousePos;

    sf::Vector2f position; // X, Y
    sf::View playerView{position, {650, 650}};

    sf::RectangleShape objOnScreen {sf::Vector2f(50, 50)};

    Player() : position({1500, 1500}), heldWeapon(*this){

        objOnScreen.setOrigin(objOnScreen.getLocalBounds().getCenter());
        heldWeapon.objectOnScreen.setPosition(position);
    }

    void update(const float dt, sf::RenderWindow &window) {

        // Handling Events

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

        // Clamp Player to Map

        position.x = floatClamp(position.x, objOnScreen.getSize().x / 2, 3000 - objOnScreen.getSize().x / 2);
        position.y = floatClamp(position.y, objOnScreen.getSize().y / 2, 3000 - objOnScreen.getSize().y / 2);

        objOnScreen.setPosition(position);

        // Need to Clamp playerView to map.

        const sf::Vector2f camSize = playerView.getSize();

        const float camX = floatClamp(position.x, camSize.x / 2, 3000 - camSize.x);
        const float camY = floatClamp(position.y, camSize.y / 2, 3000 - camSize.y);

        const sf::Vector2f camView {camX, camY};

        playerView.setCenter(camView); // Set View to Player Pos

        // Get Mouse Pos on screen, then set mousePos to the co-ords in game.

        const sf::Vector2i mouseOnScreen = sf::Mouse::getPosition(window);
        mousePos = window.mapPixelToCoords(mouseOnScreen);

        // std::cout << mousePos.x << ", " << mousePos.y << std::endl;

        heldWeapon.update(mousePos);
        heldWeapon.draw(window);

    }

    void draw(sf::RenderWindow& window) const {
        window.draw(objOnScreen);
        heldWeapon.draw(window);
    }
};

void Weapon::lookAtMouse(const sf::Vector2f mousePosition) {
    const float dx = mousePosition.x - objectOnScreen.getPosition().x;
    const float dy = mousePosition.y - objectOnScreen.getPosition().y;

    const float rotationRadians = std::atan2(dy, dx);

    const sf::Angle angleRot = sf::radians(rotationRadians);

    objectOnScreen.setRotation(angleRot);
}

void Weapon::update(const sf::Vector2f mousePosition) {
    lookAtMouse(mousePosition);
    objectOnScreen.setPosition(Parent.position);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Top Down Shooter");

    const sf::Texture mapTexture {"assets/testMap.jpg"};
    const sf::Sprite mapSprite(mapTexture);

    sf::Clock dtClock;

    Player player;

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

    const auto onMousePressed = [&](const sf::Event::MouseButtonPressed& mouseButtonPressed) {
        if (mouseButtonPressed.button == sf::Mouse::Button::Left) {
            std::cout << player.mousePos.x << ", " << player.mousePos.y << std::endl;
        }
    };


    window.setVerticalSyncEnabled(true); // VSync

    while (window.isOpen()) {

        const float dt = dtClock.restart().asSeconds();

        window.handleEvents(onClose, onKeyPressed, onMousePressed); // One Off Keycodes

        window.setView(player.playerView);
        window.clear(sf::Color::Black);
        window.draw(mapSprite); // Draw the map

        player.update(dt, window);
        player.draw(window); // Draw the player

        window.display();
    }
    return 0;
}