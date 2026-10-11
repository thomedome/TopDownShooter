#ifndef TOPDOWNSHOOTER_HEALTHBAR_H
#define TOPDOWNSHOOTER_HEALTHBAR_H
#include "SFML/Graphics.hpp"
#include "common.h"

class Entity;

class healthbar {
    public:
        void update (sf::Vector2f entityPosition, float currentHealth, float maxHealth);
        void draw(sf::RenderWindow& window);
        healthbar(Entity& parent);
protected:
    sf::RectangleShape healthBarBG {{55.f, 15.f}};
    sf::RectangleShape healthBarFill {{50.f, 10.f}};
    Entity& Parent;
};


#endif //TOPDOWNSHOOTER_HEALTHBAR_H