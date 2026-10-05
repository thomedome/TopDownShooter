//
// Created by win11 on 04/10/2026.
//

#include "Weapon.h"
#include "Bullet.h"
#include "common.h"
#include "SFML/Graphics/Color.hpp"

Weapon::Weapon(Player& owner) : Parent(owner) {
    objectOnScreen.setFillColor(sf::Color::Black);
    objectOnScreen.setOrigin({-10.f, objectOnScreen.getSize().y / 2}); // This is a test weapon for now... unless I want to make cube warfare ;p
}

void Weapon::draw(sf::RenderWindow& window) const {
    window.draw(objectOnScreen);
}

Bullet Weapon::createBullet() const {
    const BulletData bulletData {Parent.getPosition(), Parent.getMousePosition(), Range, damage, projectileVelocity};
    return Bullet {bulletData};
}