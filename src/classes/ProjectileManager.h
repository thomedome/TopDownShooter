//
// Created by win11 on 05/10/2026.
//

#ifndef TOPDOWNSHOOTER_PROJECTILEMANAGE_H
#define TOPDOWNSHOOTER_PROJECTILEMANAGE_H

#include "Bullet.h"
#include "common.h"
#include <vector>

class GameHandler;
class Weapon;

class ProjectileManager {
    std::vector<Bullet> AllBullets;
    GameHandler& ghRef;
public:
    void addBullet(Weapon& weapon);
    void updateProjectiles(const float dt, sf::RenderWindow& window);

    std::vector<Bullet>& getBullets();

    ProjectileManager(GameHandler& gh);
};

#endif //TOPDOWNSHOOTER_PROJECTILEMANAGE_H
