//
// Created by win11 on 05/10/2026.
//

#include "ProjectileManager.h"
#include "GameHandler.h"
#include "Bullet.h"

ProjectileManager::ProjectileManager(GameHandler& gh) : ghRef(gh) {}

void ProjectileManager::addBullet(Weapon& weapon) {
    const Bullet newBullet = weapon.createBullet();
    AllBullets.push_back(newBullet);
}

void ProjectileManager::updateProjectiles(const float dt, sf::RenderWindow& window) {
    std::vector<Bullet> survivors;
    survivors.reserve(AllBullets.size()); // Pre-allocate memory for speed

    for (auto& bullet : AllBullets) {
        if (!bullet.destroyFlag) {
            survivors.push_back(std::move(bullet));
        }
    }

    AllBullets.swap(survivors);

    for (auto& bullet : AllBullets) {
        bullet.update(dt);
        bullet.draw(window);
    }
}
