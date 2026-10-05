//
// Created by win11 on 05/10/2026.
//

#ifndef TOPDOWNSHOOTER_BULLET_H
#define TOPDOWNSHOOTER_BULLET_H

#include <cmath>
#include "common.h"
#include "SFML/Graphics.hpp"

class Bullet {

public:
    bool playerMomentum {false};

    float dirX {};
    float dirY {};

    float distanceTravelled {};

    bool destroyFlag {false};

    Bullet(const BulletData& bd) // Constructor
    : position(bd.posToSpawn), Range(bd.Range), damage(bd.damage), moveSpeed(bd.moveSpeed), destination(bd.destination)
    {
        // Calculating the direction vector (Target Pos - Current Pos)

        dirX = destination.x - position.x;
        dirY = destination.y - position.y;

        objectOnScreen.setFillColor(sf::Color::Yellow);
        objectOnScreen.setOutlineColor(sf::Color::Black);
        objectOnScreen.setOutlineThickness(1.f);

        // if (owner.getPlayerState() == Moving) {
        //     moveSpeed += owner.moveSpeed;
        // }

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


#endif //TOPDOWNSHOOTER_BULLET_H
