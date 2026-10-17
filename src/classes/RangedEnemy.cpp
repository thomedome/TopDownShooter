//
// Created by 30264651 on 12/10/2026.
//

#include "RangedEnemy.h"

#include <fstream>
#include <iostream>

#include "common.h"

void RangedEnemy::loadRangedStats(const nlohmann::json& json) {
    const std::string eName = to_string(enemyType);
    bufferRange = json[eName]["BufferRange"].get<float>();
    retreatRange = static_cast<float>(attackRange / 1.5);
    shootingCD = json[eName]["AttackCooldown"].get<float>();
    damage = json[eName]["AttackDamage"].get<int>();

    heldWeapon = std::make_unique<Weapon>(*this, damage);
}

RangedEnemy::RangedEnemy(sf::Vector2f spawnPosition, Player &Target) : Enemy(spawnPosition, Target, Ranged) {
    Enemy::fulfillStats(Ranged);

    std::ifstream ifs("assets/config/enemyConfig.json");

    if (!ifs.is_open()) {
        std::cerr << "Couldn't open enemyConfig file..." << std::endl;
        return;
    }

    nlohmann::json configFile = nlohmann::json::parse(ifs);

    loadRangedStats(configFile);

    objOnScreen.setFillColor(Colours::Purple);
}

void RangedEnemy::move(sf::Vector2f targetDir, sf::Vector2f separationVector, const float dt) {
    sf::Vector2f combinedDirection = targetDir + separationVector;

    // Normalize the final vector so speed remains constant
    if (combinedDirection.length() > 0.001f) {
        combinedDirection = combinedDirection.normalized();
    } else {
        combinedDirection = sf::Vector2f(0.f, 0.f);
    }

    sf::Vector2f delta = Target.getPosition() - getPosition();
    float dist = delta.length();

    if (dist < attackRange + bufferRange && dist > retreatRange) {
        currentState = Firing;
    } else if (dist < retreatRange) {
        currentState = Retreat;
        mapPosition -= combinedDirection * (moveSpeed / 2) * dt;
    } else if (dist > attackRange) {
        currentState = Approaching;
        mapPosition += combinedDirection * moveSpeed * dt;
    }

    // mapPosition += combinedDirection * moveSpeed * dt;

    // Grid and screen sync
    spatialCell = sf::Vector2i(
        std::floor(static_cast<int>(mapPosition.x) / spacialCellSize),
        std::floor(static_cast<int>(mapPosition.y) / spacialCellSize)
    );
    objOnScreen.setPosition(mapPosition);
}

Weapon *RangedEnemy::getWeapon() {
    return heldWeapon.get();
}

RangedEnemyState RangedEnemy::getState() const {
    return currentState;
}

void RangedEnemy::update(float deltaTime) {
    Enemy::update(deltaTime);
    heldWeapon->update(Target.getPosition());

    if (getAttackTimer() <= 0.0f && currentState == Firing) {
        wantsToFire = true;
        // Gets updated within ProjManager

        attackTimer = shootingCD;
    }
}

bool RangedEnemy::getFiringFlag() const {
    return wantsToFire;
}

void RangedEnemy::setFiringFlag(bool firingFlag) {
    wantsToFire = firingFlag;
}

void RangedEnemy::draw(sf::RenderWindow &window) {
    Enemy::draw(window);
    heldWeapon->draw(window);
}
