#include "GameHandler.h"
#include "ProjectileManager.h"

void GameHandler::tick(const float dt) {
    window.setView(player.getPlayerView());
    window.clear(sf::Color::Black);
    window.draw(mapSprite); // Draw the map lowest

    player.update(dt, window);
    player.draw(window); // Draw the player + gun

    updateEnemies(dt);
    projectileManager.updateProjectiles(dt, window);
}

GameHandler::GameHandler(Player& playerRef, sf::RenderWindow& windowRef, const sf::Sprite& mapSpriteRef) : player(playerRef), window(windowRef), mapSprite(mapSpriteRef) {}

void GameHandler::createEnemy(const Enemy &newEnemy) {
    allEnemies.push_back(newEnemy);
}

void GameHandler::updateEnemies(const float dt) {

    spatialGridCells.clear();

    for (auto& enemy : allEnemies) {
        enemy.update(dt);
        enemy.draw(window);

        const sf::Vector2i Cell;
        spatialGridCells[Cell.x][Cell.y].push_back(&enemy);
    }
}

std::vector<Enemy*> GameHandler::getEnemiesInSpatialCell(const sf::Vector2i Cell) {
    return spatialGridCells[Cell.x][Cell.y];
}