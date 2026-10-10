#include "GameHandler.h"

#include <algorithm>
#include <iostream>

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

void GameHandler::createEnemy(sf::Vector2f spawnPosition, Player& playerReference) {
    allEnemies.push_back(std::make_unique<Enemy>(spawnPosition, playerReference));
}

void GameHandler::updateEnemies(const float dt) {

    // clear out spatial cell grid
    for (int x = 0; x < mapWidth / spacialCellSize; ++x) {
        for (int y = 0; y < mapHeight / spacialCellSize; ++y) {
            spatialGridCells[x][y].clear();
        }
    }

    allEnemies.erase(
       std::remove_if(
           allEnemies.begin(),
           allEnemies.end(),
           [](const auto& enemy) {
               return !enemy->isAlive();
           }
       ),
       allEnemies.end()
       );

    for (const auto& enemy : allEnemies) {
        enemy->update(dt);

        sf::Vector2i Cell {enemy->getSpatialCell()};

        Cell.x = std::clamp(Cell.x, 0, mapWidth / spacialCellSize - 1);
        Cell.y = std::clamp(Cell.y, 0, mapHeight / spacialCellSize - 1);

        spatialGridCells[Cell.x][Cell.y].push_back(enemy.get());
    }

    for (auto& enemy : allEnemies) {
        const sf::Vector2i Cell {enemy->getSpatialCell()};

        std::vector<Enemy*> inCell = getEnemiesInRelativeCell(Cell);

        sf::Vector2f separation {0.f, 0.f};

        for (const auto& enemy2 : inCell) {
            if (enemy2 == enemy.get()) {
                continue;
            }

            sf::Vector2f delta = enemy->getPosition() - enemy2->getPosition();
            float distance = delta.length();
            float sepRadius = enemy->objOnScreen.getSize().x + 40.f;

            if (distance > 0.f && distance < sepRadius) {
                float force = (sepRadius - distance) / sepRadius;

                if (distance > 0.001f) {
                    separation += (delta / distance) * force;
                }
            }
        }

        sf::Vector2f targetPos = enemy->Target.getPosition();
        sf::Vector2f targetDelta = targetPos - enemy->getPosition();
        sf::Vector2f targetDir{0.f, 0.f};

        if (targetDelta.length() > 2.f) {
            targetDir = targetDelta.normalized();
        }

        enemy->move(targetDir, separation, dt);

        enemy->draw(window);
    }

    for (auto& bullet : projectileManager.getBullets()) {
        const sf::Vector2i testingCell = bullet.getSpatialCell();
        std::vector<Enemy*> enemiesInCell = getEnemiesInRelativeCell(testingCell);

        for (auto enemy : enemiesInCell) {
            if (bullet.getBounds().findIntersection(enemy->getBounds())) {
                bullet.destroyFlag = true;
                int dmg = bullet.getDamage();

                enemy->takeDamage(dmg);
            }
        }
    }
}

std::vector<Enemy*> GameHandler::getEnemiesInSpatialCell(const sf::Vector2i Cell) {
    return spatialGridCells[Cell.x][Cell.y];
}

std::vector<Enemy*> GameHandler::getEnemiesInRelativeCell(const sf::Vector2i Cell) {
    std::vector<Enemy*> returning{};

    const int gridWidth = mapWidth / spacialCellSize;
    const int gridHeight = mapHeight / spacialCellSize;

    for (int xOffset = -1; xOffset <= 1; ++xOffset) {
        for (int yOffset = -1; yOffset <= 1; ++yOffset) {

            const int x = Cell.x + xOffset;
            const int y = Cell.y + yOffset;

            // Skip cells outside the map
            if (x < 0 || x >= gridWidth || y < 0 || y >= gridHeight) { continue; }

            const auto& cell = spatialGridCells[x][y];

            returning.insert(returning.end(), cell.begin(), cell.end());
        }
    }
    return returning;
}