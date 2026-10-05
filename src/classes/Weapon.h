#ifndef TOPDOWNSHOOTER_WEAPON_H
#define TOPDOWNSHOOTER_WEAPON_H

#include "SFML/Graphics.hpp"
#include "common.h"

class Player;

class Weapon {
public:
    int damage {};
    int Range {500};
    float projectileVelocity {300.f};

    Player& Parent;
    const std::string name {};

    sf::RectangleShape objectOnScreen{{25, 10}};

    explicit Weapon(Player& owner);

    void fireBullet() const;

    void lookAtMouse(sf::Vector2f mousePosition);

    void update(sf::Vector2f mousePosition);

    void draw(sf::RenderWindow& window) const;
};

#endif //TOPDOWNSHOOTER_WEAPON_H