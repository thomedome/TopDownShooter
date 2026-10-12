//
// Created by win11 on 11/10/2026.
//

#include "MeleeEnemy.h"
#include <cmath>
#include <iostream>

void MeleeEnemy::update(const float dt) {
    Enemy::update(dt); // maintain enemy update function

    std::cout << "Updating" << std::endl;

    // attackTimer tick inherited ^^
    if (distanceToTarget < attackRange && getAttackTimer() <= 0.0f) {
        std::cout << "Attacking!" << std::endl;
        attack();
    }
}


// This logic can be recycled because the original basic enemy was essentially a melee enemy without any fancy schnizz
void MeleeEnemy::move(sf::Vector2f targetDir, const sf::Vector2f separationVector, const float dt) {
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

MeleeEnemy::MeleeEnemy(sf::Vector2f spawnPosition, Player &Target) : Enemy(spawnPosition, Target, EnemyType::Melee) {

}
