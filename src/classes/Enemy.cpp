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
}

void Enemy::update(const float dt) {

    const float dirX = Target.getPosition().x - mapPosition.x;
    const float dirY = Target.getPosition().y - mapPosition.y;

    // Get Distance via Pythagorean Theorem
    const float dist = std::sqrt(std::pow(dirX, 2.f) + std::pow(dirY, 2.f));

    // Step Size for this frame.

    const float step = moveSpeed * dt;

    if (dist <= step || dist == 0.0f) {
        return;
    }
    mapPosition = sf::Vector2f(mapPosition.x + (dirX / dist) * step, mapPosition.y + (dirY / dist) * step);

    spatialCell = sf::Vector2i(std::floor(static_cast<int>(mapPosition.x) / spacialCellSize), std::floor(static_cast<int>(mapPosition.y) / spacialCellSize));

    objOnScreen.setPosition(mapPosition);

}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(objOnScreen);
}

sf::FloatRect Enemy::getBounds() const {
    return objOnScreen.getGlobalBounds();
}