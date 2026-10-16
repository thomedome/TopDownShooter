//
// Created by win11 on 04/10/2026.
//

#include "Player.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include "../json.hpp"

#include "Weapon.h"

Player::Player(const sf::Vector2f spawnPosition) {
    std::ifstream ifs ("../src/config/config.json");

    if (!ifs.is_open()) {
        std::cerr << "Cannot open player config..." << std::endl;
        return;
    }

    nlohmann::json configFile = nlohmann::json::parse(ifs);

    damageInGun = configFile["PlayerSettings"]["WeaponFiringDamage"].get<int>();

    heldWeapon = std::make_unique<Weapon>(*this, damageInGun);
    mapPosition = spawnPosition;
    objOnScreen.setOrigin(objOnScreen.getLocalBounds().getCenter());
    heldWeapon->objectOnScreen.setPosition(mapPosition);
    entityTeam = Team::Player;
}

PlayerState Player::getPlayerState() const {
    return playerState;
}

void Player::update(const float dt, const sf::RenderWindow &window) {

    if (!isAlive()) {
        if (isDying) {
            deathTweenTime += dt;

            float t = deathTweenTime / deathTweenDuration;
            t = std::clamp(t, 0.f, 1.f);
            // Bezier Blend Curve
            t = t * t * (3.0f - 2.0f * t);

            sf::Vector2f newCamSize = deathCamStartSize + (deathCamEndSize - deathCamStartSize) * t;

            playerView.setSize(newCamSize);

            if (t >= 1.f) {
                isDying = false;
                restartFlag = true;
            }

            return;
        }
    } else { // Is alive and well
        // Handling Events

        sf::Vector2f movementVector;

        using namespace sf::Keyboard;
        if (isKeyPressed(Key::D)) {
            movementVector.x += 1.f;
        }

        if (isKeyPressed(Key::A)) {
            movementVector.x -= 1.f;
        }

        if (isKeyPressed(Key::S)) {
            movementVector.y += 1.f;
        }

        if (isKeyPressed(Key::W)) {
            movementVector.y -= 1.f;
        }

        // Normalized Movement
        if (movementVector != sf::Vector2f(0.f, 0.f)) {
            playerState = Moving;

            movementVector = movementVector.normalized();

            const sf::Vector2f nextPos {movementVector * (moveSpeed * dt)};

            mapPosition += nextPos;
        } else {
            playerState = Stationary;
        }

        spatialCell = sf::Vector2i(std::floor(static_cast<int>(mapPosition.x) / spacialCellSize), std::floor(static_cast<int>(mapPosition.y) / spacialCellSize));

        // Clamp Player to Map

        mapPosition.x = std::clamp(mapPosition.x, objOnScreen.getSize().x / 2, 3000 - objOnScreen.getSize().x / 2);
        mapPosition.y = std::clamp(mapPosition.y, objOnScreen.getSize().y / 2, 3000 - objOnScreen.getSize().y / 2);

        objOnScreen.setPosition(mapPosition);

        // Need to Clamp playerView to map.

        const sf::Vector2f camSize = playerView.getSize();

        const float camX = std::clamp(mapPosition.x, camSize.x / 2, 3000 - camSize.x / 2);
        const float camY = std::clamp(mapPosition.y, camSize.y / 2, 3000 - camSize.y / 2);

        const sf::Vector2f camView {camX, camY};

        // Get Mouse Pos on screen, then set mousePos to the co-ords in game.

        const sf::Vector2i mouseOnScreen = sf::Mouse::getPosition(window);
        mousePos = window.mapPixelToCoords(mouseOnScreen);

        playerView.setCenter(camView); // Set View to Player Pos

        heldWeapon->update(mousePos);
        healthBar.update(getPosition(), static_cast<int>(getHealth()), static_cast<int>(getMaxHealth()));

        if (invinciblityTimer > 0.f) {
            invincible = true;
            invinciblityTimer -= dt;
        } else {
            invincible = false;
            invinciblityTimer = 0.f;
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(objOnScreen);
    heldWeapon->draw(window);
    healthBar.draw(window);
}

sf::Vector2f Player::getMousePosition() const {
    return mousePos;
}

sf::Vector2f Player::getPosition() const {
    return mapPosition;
}

sf::View& Player::getPlayerView() {
    return playerView;
}

Weapon *Player::getWeapon() {
    return heldWeapon.get();
}

void Player::Death() {
    if (isDying) {return;}

    isDying = true;
    deathTweenTime = 0;
}

void Player::takeDamage(int damage) {
    if (isAlive()) {
        if (!isInvincible()) {
            health -= damage;

            if (!isAlive()) {
                Death();
            }

            invinciblityTimer = attackInvincibilityTimer;
        }
    }
}

void Player::addScore(int addingScore) {
    score += addingScore;
}

int Player::getScore() const {
    return score;
}

bool Player::getRestartFlag() const {
    return restartFlag;
}

sf::FloatRect Player::getBounds() const {
    return objOnScreen.getGlobalBounds();
}
