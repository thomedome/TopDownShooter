//
// Created by win11 on 17/10/2026.
//

#include "MapManager.h"

#include <iostream>

#include "Walkable.h"
#include "../json.hpp"

void MapManager::drawAll(sf::RenderWindow &window) {
    // std::cout << currentMaptiles.size() << std::endl;
    for (auto tile : currentMaptiles) {
        tile.draw(window);
    }
}

void MapManager::loadMap(const int mapNum) {
    std::string mapName {"map"};
    mapName += std::to_string(mapNum);
    mapName += ".txt";

    std::ifstream mapFile("assets/maps/" + mapName);

    if (!mapFile) {
        std::cout << "Unable to open file";
        return;
    }

    std::cout << "Loading map " << mapName << std::endl;

    std::string currentLine;
    int y = 0;

    while (std::getline(mapFile, currentLine)) {
        for (int x = 0; x < currentLine.length(); x++) {
            auto currentChar = currentLine[x];
            if (currentChar == '#') {
                Wall newWall {x, y};
                currentMaptiles.push_back(newWall);
            } else if (currentChar == '.') {
                Walkable newWalkable {x, y};
                currentMaptiles.push_back(newWalkable);
            }
        }

        y++;
    }
}

std::vector<Tile> MapManager::getCurrentMapTiles() {
    return currentMaptiles;
}
