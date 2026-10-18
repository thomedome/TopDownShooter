//
// Created by win11 on 17/10/2026.
//

#include "Walkable.h"

Walkable::Walkable(const int cellX, const int cellY) : Tile(cellX, cellY){
    objOnScreen.setFillColor(sf::Color::Blue);
    objOnScreen.setOutlineColor(sf::Color::Blue);
    objOnScreen.setOutlineThickness(5);
}
