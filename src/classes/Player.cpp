//
// Created by win11 on 04/10/2026.
//

#include "Player.h"

Player::Player(sf::Vector2f spawnPosition) {

    mapPosition = spawnPosition;
    objOnScreen.setOrigin(objOnScreen.getLocalBounds().getCenter());
    heldWeapon = this*;
    // heldWeapon.objectOnScreen.setPosition(position);
}