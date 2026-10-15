//
// Created by win11 on 04/10/2026.
//

#include "Weapon.h"
#include "Bullet.h"
#include "common.h"
#include "Enemy.h"
#include "Player.h"
#include "SFML/Graphics/Color.hpp"

Weapon::Weapon(Entity& owner, int DamagePerShot) : Parent(owner), damage(DamagePerShot) {
    objectOnScreen.setFillColor(sf::Color::Black);
    objectOnScreen.setOrigin({-10.f, objectOnScreen.getSize().y / 2}); // This is a test weapon for now... unless I want to make cube warfare ;p
}

void Weapon::draw(sf::RenderWindow& window) const {
    window.draw(objectOnScreen);
}

Bullet Weapon::createBullet() const {

    switch (Parent.getTeam()) {
        case Team::Player: {
            auto* playerCast = dynamic_cast<Player*>(&Parent);
            return Bullet{ BulletData{playerCast->getPosition(), playerCast->getMousePosition(), Range, damage, projectileVelocity}, Team::Player };
        }

        case Team::Enemy: {
            auto* enemyCast = dynamic_cast<Enemy*>(&Parent);
            return Bullet{ BulletData{enemyCast->getPosition(), enemyCast->Target.getPosition(), 3000, damage, projectileVelocity}, Team::Enemy };
        }

        default:
            throw std::runtime_error("Unknown team type");
    }
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