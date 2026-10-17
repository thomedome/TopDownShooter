//
// Created by win11 on 17/10/2026.
//

#ifndef TOPDOWNSHOOTER_MAPMANAGER_H
#define TOPDOWNSHOOTER_MAPMANAGER_H

#include <fstream>

#include "Wall.h"

class MapManager {
public:
    void loadMap(const int mapNum);

    std::vector<Tile> getCurrentMapTiles();
private:
    std::vector<Tile> currentMaptiles;

};


#endif //TOPDOWNSHOOTER_MAPMANAGER_H
