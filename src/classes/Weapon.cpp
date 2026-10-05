//
// Created by win11 on 04/10/2026.
//

#include "Weapon.h"
#include "Bullet.h"
#include "common.h"
#include "Player.h"
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

void Weapon::update(const sf::Vector2f mousePosition) {
    lookAtMouse(mousePosition);
    objectOnScreen.setPosition(Parent.getPosition());
}

void Weapon::lookAtMouse(const sf::Vector2f mousePosition) {
    const float dx = mousePosition.x - objectOnScreen.getPosition().x;
    const float dy = mousePosition.y - objectOnScreen.getPosition().y;

    const float rotationRadians = std::atan2(dy, dx);

    const sf::Angle angleRot = sf::radians(rotationRadians);

    objectOnScreen.setRotation(angleRot);
}