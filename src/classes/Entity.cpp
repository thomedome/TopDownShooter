//
// Created by win11 on 04/10/2026.
//

#include "Entity.h"

int Entity::getHealth() const {
    return health;
}

std::string Entity::getName() {
    return name;
}

bool Entity::isAlive() const {
    return health > 0;
}

sf::Vector2i Entity::getSpatialCell() const {
    return spatialCell;
}

void Entity::takeDamage(int damage) {
    if (isAlive()) {
        health -= damage;
    }
}

sf::Vector2f Entity::getPosition() const {
    return mapPosition;
}

void Entity::setPosition(const sf::Vector2f& position) {
    mapPosition = position;
}