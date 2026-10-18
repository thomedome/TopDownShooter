//
// Created by win11 on 17/10/2026.
//

#ifndef TOPDOWNSHOOTER_WALKABLE_H
#define TOPDOWNSHOOTER_WALKABLE_H

#include "Tile.h"

class Walkable : public Tile {
    public:
    Walkable(const int cellX, const int cellY);
};


#endif //TOPDOWNSHOOTER_WALKABLE_H