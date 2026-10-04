//
// Created by win11 on 04/10/2026.
//

#ifndef TOPDOWNSHOOTER_PLAYER_H
#define TOPDOWNSHOOTER_PLAYER_H

#include <algorithm>

#include "Entity.h"
#include "enums.h"
#include "Weapon.h"

class GameHandler;
class Weapon;

class Player : Entity {
public:
    PlayerState getPlayerState();

private:
    sf::Vector2f mousePos;
    Weapon heldWeapon;
    PlayerState playerState {Stationary};
};

class Player {

public:

    // std::vector<Bullet> ownedBullets; NEEDS TO BE MOVED TO GAMEHANDLER

    sf::View playerView{position, {750, 750}};

    sf::RectangleShape objOnScreen {sf::Vector2f(50, 50)};

    GameHandler* ghRef {nullptr};

    Player() : heldWeapon(*this), position({1500, 1500}){

        objOnScreen.setOrigin(objOnScreen.getLocalBounds().getCenter());
        heldWeapon.objectOnScreen.setPosition(position);
    }

    void update(const float dt, const sf::RenderWindow &window) {

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

            position += nextPos;
        } else {
            playerState = Stationary;
        }

        // Clamp Player to Map

        position.x = std::clamp(position.x, objOnScreen.getSize().x / 2, 3000 - objOnScreen.getSize().x / 2);
        position.y = std::clamp(position.y, objOnScreen.getSize().y / 2, 3000 - objOnScreen.getSize().y / 2);

        objOnScreen.setPosition(position);

        // Need to Clamp playerView to map.

        const sf::Vector2f camSize = playerView.getSize();

        const float camX = std::clamp(position.x, camSize.x / 2, 3000 - camSize.x / 2);
        const float camY = std::clamp(position.y, camSize.y / 2, 3000 - camSize.y / 2);

        const sf::Vector2f camView {camX, camY};

        // Get Mouse Pos on screen, then set mousePos to the co-ords in game.

        const sf::Vector2i mouseOnScreen = sf::Mouse::getPosition(window);
        mousePos = window.mapPixelToCoords(mouseOnScreen);

        playerView.setCenter(camView); // Set View to Player Pos

        heldWeapon.update(mousePos);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(objOnScreen);
        heldWeapon.draw(window);
    }
};

#endif //TOPDOWNSHOOTER_PLAYER_H