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
        sf::FloatRect getBounds() const;
        void move(const sf::Vector2f direction, const sf::Vector2f separationVector, const float dt);
        void attack(Entity& Target); // Just a float-y idea, some enemy classes / some debuff would attack others. So keep entity class instead of just player.
        float getAttackTimer();
    private:
        sf::Vector2f targetDirection;
        float attackTimer {0.0f};
};



#endif //TOPDOWNSHOOTER_ENEMY_H
