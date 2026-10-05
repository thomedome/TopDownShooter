
#include "Bullet.h"

#include "Enemy.h"

void Bullet::update(const float dt) {

    // Get Distance via Pythagorean Theorem
    const float dist = std::sqrt(std::pow(dirX, 2.f) + std::pow(dirY, 2.f));

    // Step Size for this frame.

    const float step = moveSpeed * dt;

    distanceTravelled += step;

    if (dist <= step || dist == 0.0f || distanceTravelled >= static_cast<float>(Range)) {
        destroyFlag = true;
        return;
    }

    position = sf::Vector2f(position.x + (dirX / dist) * step, position.y + (dirY / dist) * step);

    SpatialCell = sf::Vector2i(std::floor(static_cast<int>(position.x) / spacialCellSize), std::floor(static_cast<int>(position.y) / spacialCellSize));

    objectOnScreen.setPosition(position);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(objectOnScreen);
}

sf::Vector2i Bullet::getSpatialCell() const {
    return SpatialCell;
}

sf::FloatRect Bullet::getBounds() {
    return objectOnScreen.getGlobalBounds();
}

int Bullet::getDamage() {
    return damage;
}