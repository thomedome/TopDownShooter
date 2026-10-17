#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "classes/Player.h"
#include "classes/common.h"
#include "classes/GameHandler.h"
#include "classes/ProjectileManager.h"
#include "json.hpp"
#include "classes/WaveManager.h"

sf::Font font("assets/fonts/LiberationSans-Regular.ttf");

bool testingMap = false;

// , sf::State::Fullscreen
int main() {
    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(windowHeight * aspectRatio), windowHeight}), "Top Down Shooter");
    window.setVerticalSyncEnabled(true); // VSync

    while (window.isOpen()) {

        // Testing Map Definition
        const sf::Texture mapTexture {"assets/testMap.jpg"};
        sf::Sprite mapSprite(mapTexture);

        sf::Text FPSObj {font, "FPS: XX"};
        float dtAccum {0.f}; // fps timer
        float fpsTime {.5f};
        float frameCount {0}; // float for the sake of narrowing conversion
        int fps {};

        sf::Text WaveObj{font, "Wave: 1"};
        sf::Text ScoreOBj{font, "Score: 0"};

        std::ifstream ifs("assets/config/config.json");

        if (!ifs.is_open()) {
            std::cerr << "Couldn't open config file..." << std::endl;
            return 0;
        }

        nlohmann::json configFile = nlohmann::json::parse(ifs);

        int wave = 0;
        int allocatedBudget;
        int startingBudget = configFile["WaveSettings"]["StartingBudget"].get<int>();

        ifs.close();

        WaveManager waveManager {startingBudget};

        sf::Clock dtClock;

        Player player {sf::Vector2f(1500, 1500)};
        GameHandler gameHandler(player, window, mapSprite, waveManager);

        const auto onClose = [&window](const sf::Event::Closed&)
        {
            window.close();
        };

        const auto onKeyPressed = [&window, &gameHandler](const sf::Event::KeyPressed& keyPressed)
        {
            if (keyPressed.scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }

            if (keyPressed.scancode == sf::Keyboard::Scancode::F) {
                gameHandler.showFPS = !gameHandler.showFPS;
            }
        };

        const auto onMousePressed = [&](const sf::Event::MouseButtonPressed& mouseButtonPressed) {
            if (mouseButtonPressed.button == sf::Mouse::Button::Left) {
                if (player.isAlive()) {
                    gameHandler.projectileManager.addBullet(player.getWeapon());
                }
            }
        };

        while (window.isOpen()) {

            if (player.getRestartFlag()) {
                break;
            }

            const float dt = dtClock.restart().asSeconds();

            frameCount += 1;
            dtAccum += dt;

            if (dtAccum >= fpsTime) {
                fps = static_cast<int>(std::round(frameCount / fpsTime));
                frameCount = 1;
                dtAccum -= fpsTime;
            }

            window.handleEvents(onClose, onKeyPressed, onMousePressed); // One Off Keycodes

            if (waveManager.allEnemies.empty()) {
                wave += 1;
                waveManager.incrementBudget(wave);
                waveManager.generateWave(player);
            }

            gameHandler.tick(dt);

            if (gameHandler.showFPS) {
                window.setView(window.getDefaultView());

                FPSObj.setString("FPS: " + std::to_string(static_cast<int>(std::round(fps))));
                FPSObj.setPosition({(windowHeight * aspectRatio) - 300, 10.f});

                window.draw(FPSObj);
            }

            window.setView(window.getDefaultView());

            WaveObj.setString("Wave: " + std::to_string(static_cast<int>(wave)));
            WaveObj.setPosition({10.f, 10.f});

            ScoreOBj.setString("Score: " + std::to_string(player.getScore()));
            ScoreOBj.setPosition({10.f, 50.f});

            window.draw(WaveObj);
            window.draw(ScoreOBj);

            window.setView(player.getPlayerView());

            window.display();
        }
    }
}