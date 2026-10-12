//
// Created by 30264651 on 12/10/2026.
//

#ifndef TOPDOWNSHOOTER_RANGEDENEMY_H
#define TOPDOWNSHOOTER_RANGEDENEMY_H

#include "Enemy.h"
#include "../json.hpp"

// Planning Movement:
// Variables:
//
// Buffer zone which will prevent enemy from micro-adjusting when the player moves as soon as the enemy reaches range
// Retreat Range - when the player gets too close (half firing range?) the enemy starts walking away, but slower than approach.
//
// 3 States - Approaching - Firing - Retreat (FSM)

// Approaching:
// Walk towards Range variable distance (calc dist from player, move towards)

// Firing:
// Standard firing - add weapon class to enemy

// Retreat:
// When player gets too close to the enemy, get opposite directional vector and move towards that until reaches the >range and <buffer zone.

enum RangedEnemyState {
    Approaching,
    Firing,
    Retreat
};

class RangedEnemy : public Enemy {
    public:
    void update(float deltaTime) override;
    void move(sf::Vector2f targetDir, sf::Vector2f separationVector, float dt);

    RangedEnemy(sf::Vector2f spawnPosition, Player& Target);

    RangedEnemyState getState() const;
    void loadRangedStats(const nlohmann::json& json); // Import Ranged Stats as cannot do within enemy func

    private:
    RangedEnemyState currentState {Approaching};
    float bufferRange {};
    float retreatRange {};
};


#endif //TOPDOWNSHOOTER_RANGEDENEMY_H
