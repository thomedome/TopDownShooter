//
// Created by win11 on 04/10/2026.
//

#include "Entity.h"

int Entity::getHealth() const {
    return health;
}

float Entity::getMoveSpeed() {
    return moveSpeed;
}

int Entity::getMaxHealth() const {
    return maxHealth;
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

sf::Vector2i Entity::getMapTile() const {
    return mapTile;
}

void Entity::takeDamage(int damage) {
    if (isAlive()) {
        if (!isInvincible()) {
            health -= damage;
        }
    }
}

sf::Vector2f Entity::getPosition() const {
    return mapPosition;
}

void Entity::setPosition(const sf::Vector2f& position) {
    mapPosition = position;
}

bool Entity::isInvincible() {
    return invincible;
}

Team::Team Entity::getTeam() const {
    return entityTeam;
}

void Entity::move(const sf::Vector2f pos) {
    mapPosition = pos;
}