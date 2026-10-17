//
// Created by win11 on 17/10/2026.
//

#include "Tile.h"


Tile::Tile (const int cellX, const int cellY) {
    Cell = {cellX, cellY};
    objOnScreen.setOrigin({size.x / 2, size.y / 2});
    objOnScreen.setPosition({cellX * size.x, cellY * size.y});
}

sf::FloatRect Tile::getBounds() {
    return objOnScreen.getGlobalBounds();
}

std::array<int, 2> Tile::getCell() const {
    return Cell;
}

bool Tile::getTraversable() {
    return isTraversable;
}
