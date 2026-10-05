//
// Created by win11 on 05/10/2026.
//

#ifndef TOPDOWNSHOOTER_GAMEHANDLER_H
#define TOPDOWNSHOOTER_GAMEHANDLER_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "ProjectileManager.h"

class GameHandler { // Used to hold what objects needs updating + rendering, and have an overarching tick method to update everything.

public:
    Player& player;
    std::vector<std::unique_ptr<Enemy>> allEnemies;
    // Enemies go here eventually...

    ProjectileManager projectileManager{*this};
    sf::RenderWindow& window;
    sf::Sprite mapSprite;
    bool showFPS {};
    void tick(float dt);
    void updateEnemies(float dt);
    void createEnemy(const Enemy& newEnemy);
    std::vector<Enemy*> getEnemiesInSpatialCell(sf::Vector2i Cell);

    std::vector<Enemy*> spatialGridCells [mapWidth / spacialCellSize][mapHeight / spacialCellSize] {}; // 100 x 100 cell size. makes 30 cells for now.

    // Cells will be start, start + size to index. so Cell [0, 0] will be between (0, 100)x and (0, 100)y

    GameHandler(Player &playerRef, sf::RenderWindow& windowRef, const sf::Sprite& mapSpriteRef);
};


#endif //TOPDOWNSHOOTER_GAMEHANDLER_H
