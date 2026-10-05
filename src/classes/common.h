//
// Created by win11 on 05/10/2026.
//

#ifndef TOPDOWNSHOOTER_COMMON_H
#define TOPDOWNSHOOTER_COMMON_H
#include "SFML/System/Vector2.hpp"

struct BulletData {
    sf::Vector2f posToSpawn;
    sf::Vector2f destination;

    int Range;
    int damage;
    float moveSpeed;

    BulletData(sf::Vector2f pos1, sf::Vector2f pos2, int r, int d, float ms) : posToSpawn(pos1), destination(pos2), Range(r), damage(d), moveSpeed(ms) {}
};

#endif //TOPDOWNSHOOTER_COMMON_H
