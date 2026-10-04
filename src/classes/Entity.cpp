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
