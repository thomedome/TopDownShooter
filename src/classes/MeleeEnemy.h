//
// Created by win11 on 11/10/2026.
//

#ifndef TOPDOWNSHOOTER_MELEEENEMY_H
#define TOPDOWNSHOOTER_MELEEENEMY_H

#include "Enemy.h"

class MeleeEnemy : public Enemy{
public:
    MeleeEnemy(sf::Vector2f spawnPosition, Player& Target);
    void update(const float dt) override;
    void move(sf::Vector2f targetDir, sf::Vector2f separationVector, float dt);
};


#endif //TOPDOWNSHOOTER_MELEEENEMY_H
