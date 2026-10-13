//
// Created by win11 on 05/10/2026.
//

#include "Enemy.h"
#include "common.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include "../json.hpp"

// Planning out enemy refactor:

// Common Logic:
// Spatial Cell Logic
// Updating and redrawing Healthbar
// Positional Updates - moving to target direction
// Attack cooldown increase on tick
// All common helper functions
// Player Target Reference

// Class Dependent Logic
// Deciding where to move to
// Attacking
// Any extra moves

Enemy::Enemy(const sf::Vector2f spawnPosition, Player& Target, EnemyType eType) : Target(Target), enemyType(eType) {
    mapPosition = spawnPosition;
    objOnScreen.setOrigin(objOnScreen.getLocalBounds().getCenter());
    moveSpeed = {150.f};

    // This needs to change on refactor - when initialised, an Enum will be passed defining the type, then settings will follow.
    objOnScreen.setFillColor(sf::Color::Red);
    objOnScreen.setOutlineColor(sf::Color::White);
    objOnScreen.setOutlineThickness(2.0f);

    Enemy::fulfillStats(eType);
    entityTeam = Team::Enemy;
}

void Enemy::update(const float dt) {
    const float dirX = Target.getPosition().x - mapPosition.x;
    const float dirY = Target.getPosition().y - mapPosition.y;
    const float dist = std::sqrt(dirX * dirX + dirY * dirY);

    distanceToTarget = dist;

    if (dist <= 2.f || dist == 0.0f) {
        this->targetDirection = sf::Vector2f(0.f, 0.f);
        return;
    }

    this->targetDirection = sf::Vector2f(dirX / dist, dirY / dist);

    if (getAttackTimer() > 0.0f) {
        attackTimer -= dt;
    }

    healthBar.update(getPosition(), static_cast<int>(getHealth()), static_cast<int>(getMaxHealth())); // Why did i put this in the move function???
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
    healthBar.draw(window);
}

sf::FloatRect Enemy::getBounds() const {
    return objOnScreen.getGlobalBounds();
}

float Enemy::getAttackTimer() const {
    return attackTimer;
}

void Enemy::attack() {
    if (getAttackTimer() <= 0.0f) {
        // Target.takeDamage(damage); Needs to be moved to individual children classes
        attackTimer = enemyDamageCD;
    }
}

int Enemy::getScore() const {
    return score;
}

// Read from JSON
void Enemy::fulfillStats(EnemyType eType) {

    std::ifstream ifs("../src/config/enemyConfig.json");

    if (!ifs.is_open()) {
        std::cerr << "Couldn't open enemyConfig file..." << std::endl;
        return;
    }

    nlohmann::json configFile = nlohmann::json::parse(ifs);
    const std::string enemyName = to_string(eType);

    // Common Stats
    damage = configFile[enemyName]["AttackDamage"];
    attackRange = configFile[enemyName]["AttackRange"];
    health = configFile[enemyName]["Health"]; // This applies as max health
    moveSpeed = configFile[enemyName]["MoveSpeed"];
    maxHealth = health;

}
