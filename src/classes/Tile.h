//
// Created by win11 on 17/10/2026.
//

#ifndef TOPDOWNSHOOTER_TILE_H
#define TOPDOWNSHOOTER_TILE_H

#include <SFML/Graphics.hpp>

// Parent Class for all map cells

class Tile {
public:
    sf::FloatRect getBounds();
    bool getTraversable();
    std::array<int, 2> getCell() const;

    Tile(const int cellX, const int cellY);

protected:
    const sf::Vector2f size {150, 150};
    sf::RectangleShape objOnScreen {};
    std::array<int, 2> Cell;
    bool isTraversable {true};
};


#endif //TOPDOWNSHOOTER_TILE_H
