//
// Created by win11 on 17/10/2026.
//

#include "Wall.h"

Wall::Wall(const int cellX, const int cellY) : Tile(cellX, cellY) {
    isTraversable = false;
    objOnScreen.setFillColor(sf::Color::White);
    objOnScreen.setOutlineColor(sf::Color::Black);
    objOnScreen.setOutlineThickness(5);
}