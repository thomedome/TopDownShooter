#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>

sf::Font font("assets/fonts/LiberationSans-Regular.ttf");

float floatClamp(const float d, const float min, const float max) { // Thank you random man on stack overflow!
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

enum PlayerState {
    Stationary,
    Moving,
};

class Player;

class Bullet;

class GameHandler { // Used to hold what objects needs updating + rendering, and have an overarching tick method to update everything.

    public:
        Player& player; // Contains Bullet Vector
        // Enemies go here eventually...

        sf::RenderWindow& window;

        bool showFPS {};

        void tick(float dt) const;

        GameHandler(Player &playerRef, sf::RenderWindow& windowRef);
};

class Weapon {
    public:
        int damage {};
        int Range {500};
        float projectileVelocity {300.f};

        Player& Parent;
        const std::string name {};

        sf::RectangleShape objectOnScreen{{25, 10}};

        explicit Weapon(Player& owner) : Parent(owner) {
            objectOnScreen.setFillColor(sf::Color::Black);
            objectOnScreen.setOrigin({-10.f, objectOnScreen.getSize().y / 2}); // This is a test weapon for now... unless i want to make cube warfare ;p
        }

        void fireBullet(sf::Vector2f mousePosition);

        void lookAtMouse(sf::Vector2f mousePosition);

        void update(sf::Vector2f mousePosition);

        void draw(sf::RenderWindow& window) const {
            window.draw(objectOnScreen);
        }
};

class Player {

public:
    Weapon heldWeapon;
    std::vector<Bullet> ownedBullets;
    sf::Vector2f mousePos;

    int health {100};
    float moveSpeed {250.f};

    PlayerState playerState {Stationary};
    sf::Vector2f position; // X, Y
    sf::View playerView{position, {750, 750}};

    sf::RectangleShape objOnScreen {sf::Vector2f(50, 50)};

    GameHandler* ghRef {nullptr};

    Player() : heldWeapon(*this), position({1500, 1500}){

        objOnScreen.setOrigin(objOnScreen.getLocalBounds().getCenter());
        heldWeapon.objectOnScreen.setPosition(position);
    }

    void update(const float dt, sf::RenderWindow &window) {

        // Handling Events

        bool moving = false;
        sf::Vector2f movementVector;

        using namespace sf::Keyboard;
        if (isKeyPressed(Key::D)) {
            movementVector.x += 1;
            moving = true;
        }

        if (isKeyPressed(Key::A)) {
            movementVector.x -= 1;
            moving = true;
        }

        if (isKeyPressed(Key::S)) {
            movementVector.y += 1;
            moving = true;
        }

        if (isKeyPressed(Key::W)) {
            movementVector.y -= 1;
            moving = true;
        }

        if (!moving) {
            playerState = Stationary;
        } else {
            playerState = Moving;
        }

        // Normalized Movement
        if (movementVector != sf::Vector2f(0, 0)) {
            movementVector = movementVector.normalized();

            const sf::Vector2f nextPos {movementVector * (moveSpeed * dt)};

            position += nextPos;
        }

        // Clamp Player to Map

        position.x = floatClamp(position.x, objOnScreen.getSize().x / 2, 3000 - objOnScreen.getSize().x / 2);
        position.y = floatClamp(position.y, objOnScreen.getSize().y / 2, 3000 - objOnScreen.getSize().y / 2);

        objOnScreen.setPosition(position);

        // Need to Clamp playerView to map.

        const sf::Vector2f camSize = playerView.getSize();

        const float camX = floatClamp(position.x, camSize.x / 2, 3000 - camSize.x / 2);
        const float camY = floatClamp(position.y, camSize.y / 2, 3000 - camSize.y / 2);

        const sf::Vector2f camView {camX, camY};

        playerView.setCenter(camView); // Set View to Player Pos

        // Get Mouse Pos on screen, then set mousePos to the co-ords in game.

        const sf::Vector2i mouseOnScreen = sf::Mouse::getPosition(window);
        mousePos = window.mapPixelToCoords(mouseOnScreen);

        heldWeapon.update(mousePos);
        heldWeapon.draw(window);

    }

    void draw(sf::RenderWindow& window) const {
        window.draw(objOnScreen);
        heldWeapon.draw(window);
    }
};

class Bullet {

public:
    Player& owner;

    bool playerMomentum {false};

    float dirX {};
    float dirY {};

    float distanceTravelled {};

    bool destroyFlag {false};

    Bullet(const sf::Vector2f posToSpawn, const Weapon& GunOwner) // Constructor
    : owner(GunOwner.Parent), position(posToSpawn), Range(GunOwner.Range), damage(GunOwner.damage), moveSpeed(GunOwner.projectileVelocity), destination(owner.mousePos)
    {
        // Calculating the direction vector (Target Pos - Current Pos)

        std::cout << destination.x << destination.y << std::endl;
        std::cout << position.x << position.y << std::endl;

        dirX = destination.x - position.x;
        dirY = destination.y - position.y;

        std::cout << dirX << "," << dirY << std::endl;

        objectOnScreen.setFillColor(sf::Color::Yellow);
        objectOnScreen.setOutlineColor(sf::Color::Black);
        objectOnScreen.setOutlineThickness(1.f);

        if (owner.playerState == Moving) {
            moveSpeed += owner.moveSpeed;
        }

        owner.ownedBullets.push_back(*this);
    };

    void update(const float dt) {

        // Get Distance via Pythagorean Theorem
        const float dist = std::sqrt(std::pow(dirX, 2.f) + std::pow(dirY, 2.f));

        // Step Size for this frame.

        const float step = moveSpeed * dt;

        distanceTravelled += step;

        if (dist <= step || dist == 0.0f || distanceTravelled >= static_cast<float>(Range)) {
            destroyFlag = true;
            return;
        }

        position = sf::Vector2f(position.x + (dirX / dist) * step, position.y + (dirY / dist) * step);
        objectOnScreen.setPosition(position);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(objectOnScreen);
    }

private:
    sf::RectangleShape objectOnScreen{sf::Vector2f(5, 5)};
    sf::Vector2f position;

    int Range {}; // Added from constructor
    int damage {}; // ^
    float moveSpeed {300.f}; // ^
    sf::Vector2f destination{};
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

void Weapon::fireBullet(const sf::Vector2f mousePosition) {
    std::cout << "fireBullet" << std::endl;
    Bullet newBullet(Parent.position, *this);
}

void GameHandler::tick(const float dt) const {
    // std::cout << "Tick" << std::endl;
    std::vector<Bullet> survivors;
    survivors.reserve(player.ownedBullets.size()); // Pre-allocate memory for speed

    for (auto& bullet : player.ownedBullets) {
        if (!bullet.destroyFlag) {
            survivors.push_back(std::move(bullet));
        }
    }

    player.ownedBullets.swap(survivors);

    for (auto& bullet : player.ownedBullets) {
        bullet.update(dt);
        bullet.draw(window);
    }
}

GameHandler::GameHandler(Player& playerRef, sf::RenderWindow& windowRef) : player(playerRef), window(windowRef) {
    player.ghRef = this;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({750, 750}), "Top Down Shooter");

    const sf::Texture mapTexture {"assets/testMap.jpg"};
    const sf::Sprite mapSprite(mapTexture);

    sf::Text FPSObj {font, "FPS: XX"};

    sf::Clock dtClock;

    Player player;
    GameHandler gameHandler(player, window);

    const auto onClose = [&window](const sf::Event::Closed&)
    {
        window.close();
        exit(0);
    };

    const auto onKeyPressed = [&window, &gameHandler](const sf::Event::KeyPressed& keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Escape) {
            window.close();
            exit(0);
        }

        if (keyPressed.scancode == sf::Keyboard::Scancode::F) {
            gameHandler.showFPS = !gameHandler.showFPS;
            std::cout << "FPS " << std::to_string(gameHandler.showFPS);
        }
    };

    const auto onMousePressed = [&](const sf::Event::MouseButtonPressed& mouseButtonPressed) {
        if (mouseButtonPressed.button == sf::Mouse::Button::Left) {
            player.heldWeapon.fireBullet(player.mousePos);
            std::cout << player.mousePos.x << ", " << player.mousePos.y << std::endl;
        }
    };

    window.setVerticalSyncEnabled(true); // VSync

    while (window.isOpen()) {

        const float dt = dtClock.restart().asSeconds();

        const auto fps = 1 / dt;

        // std::cout << "FPS: " << fps << std::endl;

        window.handleEvents(onClose, onKeyPressed, onMousePressed); // One Off Keycodes

        window.setView(player.playerView);
        window.clear(sf::Color::Black);
        window.draw(mapSprite); // Draw the map lowest

        player.update(dt, window);
        player.draw(window); // Draw the player + gun

        gameHandler.tick(dt);

        if (gameHandler.showFPS) {
            window.setView(window.getDefaultView());

            FPSObj.setString("FPS: " + std::to_string(std::round(fps)));
            FPSObj.setPosition({10.f, 10.f});

            window.draw(FPSObj);
        }

        window.display();
    }
    return 0;
}