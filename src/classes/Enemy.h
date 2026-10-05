//
// Created by win11 on 05/10/2026.
//

#ifndef TOPDOWNSHOOTER_ENEMY_H
#define TOPDOWNSHOOTER_ENEMY_H

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
    public:
        Player& Target;
        sf::RectangleShape objOnScreen {sf::Vector2f(35, 35)};

        Enemy(sf::Vector2f spawnPosition, Player& Target);

        void update(const float dt);
        void draw(sf::RenderWindow& window);

    private:
};


#endif //TOPDOWNSHOOTER_ENEMY_H
