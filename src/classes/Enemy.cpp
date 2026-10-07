//
// Created by win11 on 05/10/2026.
//

#include "Enemy.h"
#include "common.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(const sf::Vector2f spawnPosition, Player& Target) : Target(Target) {
    mapPosition = spawnPosition;
    objOnScreen.setOrigin(objOnScreen.getLocalBounds().getCenter());
    moveSpeed = {200.f};
    objOnScreen.setFillColor(sf::Color::Red);
    objOnScreen.setOutlineColor(sf::Color::White);
    objOnScreen.setOutlineThickness(2.0f);
}

// void Enemy::move(sf::Vector2f direction, const sf::Vector2f separationVector, const float dt) {
//
//     direction += separationVector;
//
//     if (direction != sf::Vector2f(0.f, 0.f)) {
//         direction = direction.normalized();
//     }
//
//     mapPosition += direction * moveSpeed * dt;
//
//     spatialCell = sf::Vector2i(std::floor(static_cast<int>(mapPosition.x) / spacialCellSize), std::floor(static_cast<int>(mapPosition.y) / spacialCellSize));
//     objOnScreen.setPosition(mapPosition);
// }
//
// void Enemy::update(const float dt) {
//
//     const float dirX = Target.getPosition().x - mapPosition.x;
//     const float dirY = Target.getPosition().y - mapPosition.y;
//
//     // Get Distance via Pythagorean Theorem
//     const float dist = std::sqrt(std::pow(dirX, 2.f) + std::pow(dirY, 2.f));
//
//     // Step Size for this frame.
//
//     const float step = moveSpeed * dt;
//
//     if (dist <= step || dist == 0.0f) {
//         return;
//     }
//     mapPosition = sf::Vector2f(mapPosition.x + (dirX / dist) * step, mapPosition.y + (dirY / dist) * step);
// }

void Enemy::update(const float dt) {
    const float dirX = Target.getPosition().x - mapPosition.x;
    const float dirY = Target.getPosition().y - mapPosition.y;
    const float dist = std::sqrt(dirX * dirX + dirY * dirY);

    if (dist <= 2.f || dist == 0.0f) {
        this->targetDirection = sf::Vector2f(0.f, 0.f);
        return;
    }

    this->targetDirection = sf::Vector2f(dirX / dist, dirY / dist);
}

void Enemy::move(sf::Vector2f targetDir, const sf::Vector2f separationVector, const float dt) {
    // Combine target intent and soft repulsion
    sf::Vector2f combinedDirection = targetDir + separationVector;

    // Normalize the final vector so speed remains constant
    if (combinedDirection.length() > 0.001f) {
        combinedDirection = combinedDirection.normalized();
    } else {
        combinedDirection = sf::Vector2f(0.f, 0.f);
    }

    // Apply movement exactly once
    mapPosition += combinedDirection * moveSpeed * dt;

    // Grid and screen sync
    spatialCell = sf::Vector2i(
        std::floor(static_cast<int>(mapPosition.x) / spacialCellSize),
        std::floor(static_cast<int>(mapPosition.y) / spacialCellSize)
    );
    objOnScreen.setPosition(mapPosition);
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(objOnScreen);
}

sf::FloatRect Enemy::getBounds() const {
    return objOnScreen.getGlobalBounds();
}

float Enemy::getAttackTimer() {
    return attackTimer;
}


void Enemy::attack(Entity& Target) {
    if (!getAttackTimer() > 0.0f) {

    }
}