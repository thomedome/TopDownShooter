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

void GameHandler::createEnemy(const Enemy &newEnemy) {
    allEnemies.push_back(std::make_unique<Enemy>(newEnemy));
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


    for (auto& enemy : allEnemies) {

        enemy->update(dt);
        enemy->draw(window);

        const sf::Vector2i Cell {enemy->getSpatialCell()};
        spatialGridCells[Cell.x][Cell.y].push_back(enemy.get());

        std::vector<Enemy*> inCell = getEnemiesInSpatialCell(Cell);

        for (auto& enemy2 : inCell) {

            if (enemy2 == enemy.get()) {
                continue;
            }

            auto intersection = enemy->getBounds().findIntersection(enemy2->getBounds());

            if (intersection) {
                const float overlapX = intersection->size.x;
                float const overlapY = intersection->size.y;

                const float dx = enemy->getPosition().x - enemy2->getPosition().x;

                if (overlapX < overlapY) {
                    const float push = overlapX / 2.f;

                    if (dx >= 0.f) {
                        enemy->setPosition(sf::Vector2f(enemy->getPosition().x + push, enemy->getPosition().y));
                        enemy2->setPosition(sf::Vector2f(enemy2->getPosition().x - push, enemy2->getPosition().y));
                    } else {
                        enemy->setPosition(sf::Vector2f(enemy->getPosition().x - push, enemy->getPosition().y));
                        enemy2->setPosition(sf::Vector2f(enemy2->getPosition().x + push, enemy2->getPosition().y));
                    }

                } else {
                    const float push = overlapY / 2.f;

                    if (dx >= 0.f) {
                        enemy->setPosition(sf::Vector2f(enemy->getPosition().x, enemy->getPosition().y + push));
                        enemy2->setPosition(sf::Vector2f(enemy2->getPosition().x, enemy2->getPosition().y - push));
                    } else {
                        enemy->setPosition(sf::Vector2f(enemy->getPosition().x, enemy->getPosition().y - push));
                        enemy2->setPosition(sf::Vector2f(enemy2->getPosition().x, enemy2->getPosition().y + push));
                    }
                }
            }
        }
    }

    for (auto& bullet : projectileManager.getBullets()) {
        const sf::Vector2i testingCell = bullet.getSpatialCell();
        std::vector<Enemy*> enemiesInCell = getEnemiesInSpatialCell(testingCell);

        for (auto enemy : enemiesInCell) {
            if (bullet.getBounds().findIntersection(enemy->getBounds())) {
                std::cout << "Found!" << std::endl;
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