//
// Created by win11 on 05/10/2026.
//

#ifndef TOPDOWNSHOOTER_COMMON_H
#define TOPDOWNSHOOTER_COMMON_H
#include "EnemyTypes.h"
#include "SFML/Graphics.hpp"

// Colours

namespace Colours {
    const sf::Color darkRed {100, 0, 0};
    const sf::Color Purple {191, 64, 191};
}

constexpr int mapHeight = 3000;
constexpr int mapWidth = 3000;

constexpr float PI = 3.14159265358979323846f;

constexpr float aspectRatio = 16.f / 9.f;

constexpr int windowHeight = 1080;

constexpr float attackInvincibilityTimer = 0.5f;

constexpr float waveSpawnRadius = 750.f;

constexpr int spacialCellSize = 100;

constexpr float enemyDamageCD = .5f;

inline float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

struct BulletData {
    sf::Vector2f posToSpawn;
    sf::Vector2f destination;

    int Range;
    int damage;
    float moveSpeed;

    BulletData(sf::Vector2f pos1, sf::Vector2f pos2, int r, int d, float ms) : posToSpawn(pos1), destination(pos2), Range(r), damage(d), moveSpeed(ms) {}
};

struct EnemyData {
    int health {};
    int attackDamage {};
    float attackRange {};
    int score {};
    float moveSpeed {};
};

inline std::string to_string(EnemyType eType) {
    switch (eType) {
        case EnemyType::Melee: return "MeleeEnemy";
        case EnemyType::Ranged: return "RangedEnemy";
        case EnemyType::Tank:    return "TankEnemy";
        default:                return "Unknown";
    }
}

#endif //TOPDOWNSHOOTER_COMMON_H
