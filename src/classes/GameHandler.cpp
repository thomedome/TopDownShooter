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

    for (const auto& enemy : allEnemies) {
        enemy->update(dt);
        enemy->draw(window);
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

        const sf::Vector2i Cell {enemy->getSpatialCell()};
        spatialGridCells[Cell.x][Cell.y].push_back(enemy.get());

        std::vector<Enemy*> inCell = getEnemiesInSpatialCell(Cell);

        sf::Vector2f separation {0, 0};
        sf::Vector2f delta {};

        for (const auto& enemy2 : inCell) {

            if (enemy2 == enemy.get()) {
                continue;
            }

            // Enemy on Enemy Collision

            delta = enemy->getPosition() - enemy2->getPosition();

            float distance = delta.length();
            float sepRadius = enemy->objOnScreen.getSize().x + 10;

            if (distance > 0.f && distance < sepRadius) {
                separation += delta.normalized();
            }

            if (separation != sf::Vector2f{0.f, 0.f}) {
                separation = separation.normalized();

                enemy -> setPosition(enemy->getPosition() + separation * 2.5f);
            }


        }

        enemy->move(delta, separation * 2.5f, dt);
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