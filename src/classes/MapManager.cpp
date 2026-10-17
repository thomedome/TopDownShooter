//
// Created by win11 on 17/10/2026.
//

#include "MapManager.h"

#include <iostream>

#include "../json.hpp"

void MapManager::loadMap(const int mapNum) {
    std::string mapName {"map"};
    mapName += std::to_string(mapNum);
    mapName += ".txt";

    std::ifstream mapFile(mapName);

    if (!mapFile) {
        std::cout << "Unable to open file";
        return;
    }

    char tile {};

    while (mapFile.get(tile)) {
        mapFile.tellg();
        int tileNum {};
        if (tile == '.') {

        } else if (tile == '#') {
            Wall newWall {};
        }
    }
}
