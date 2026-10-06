#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <numbers>

#include "classes/Player.h"
#include "classes/Enemy.h"
#include "classes/GameHandler.h"
#include "classes/ProjectileManager.h"

sf::Font font("assets/fonts/LiberationSans-Regular.ttf");

float floatClamp(const float d, const float min, const float max) { // Thank you random man on stack overflow!
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({750, 750}), "Top Down Shooter");

    const sf::Texture mapTexture {"assets/testMap.jpg"};
    sf::Sprite mapSprite(mapTexture);

    sf::Text FPSObj {font, "FPS: XX"};
    float dtAccum {0.f}; // fps timer
    float fpsTime {.5f};
    float frameCount {0}; // float for the sake of narrowing conversion
    int fps {};

    int wave = 1;

    sf::Clock dtClock;

    Player player {sf::Vector2f(1500, 1500)};
    GameHandler gameHandler(player, window, mapSprite);

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
        }
    };

    const auto onMousePressed = [&](const sf::Event::MouseButtonPressed& mouseButtonPressed) {
        if (mouseButtonPressed.button == sf::Mouse::Button::Left) {
            gameHandler.projectileManager.addBullet(player.getWeapon());
        }
    };

    window.setVerticalSyncEnabled(true); // VSync

    while (window.isOpen()) {

        const float dt = dtClock.restart().asSeconds();

        frameCount += 1;
        dtAccum += dt;

        if (dtAccum >= fpsTime) {
            fps = static_cast<int>(std::round(frameCount / fpsTime));
            frameCount = 1;
            dtAccum -= fpsTime;
        }

        window.handleEvents(onClose, onKeyPressed, onMousePressed); // One Off Keycodes

        if (gameHandler.allEnemies.empty()) {
            wave += 1;

            sf::Vector2f playerPos {player.getPosition()};

            const auto enemyCount = static_cast<float>(wave * 3);

            for (int i = 0; i < enemyCount; ++i) {
                auto angle = 2.f * PI * i / enemyCount;
                sf::Vector2f spawnPosition {playerPos.x + std::cos(angle) * waveSpawnRadius, playerPos.y + std::sin(angle) * waveSpawnRadius};

                gameHandler.createEnemy(spawnPosition, player);
            }
        }

        gameHandler.tick(dt);

        if (gameHandler.showFPS) {
            window.setView(window.getDefaultView());

            FPSObj.setString("FPS: " + std::to_string(static_cast<int>(std::round(fps))));
            FPSObj.setPosition({10.f, 10.f});

            window.draw(FPSObj);
        }

        window.display();
    }
    return 0;
}