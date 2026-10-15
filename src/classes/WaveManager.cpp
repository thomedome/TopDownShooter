//
// Created by win11 on 14/10/2026.
//

#include "WaveManager.h"

#include <cmath>
#include <fstream>
#include <iostream>

#include "MeleeEnemy.h"
#include "RangedEnemy.h"

WaveManager::WaveManager(const int initalisedBudget) : allocatedBudget(initalisedBudget) {

    std::cout << "Current working dir: " << std::filesystem::current_path() << std::endl;

    std::ifstream ifs("../src/config/config.json");

    if (!ifs.is_open()) {
        std::cerr << "Couldn't open config file..." << std::endl;
        return;
    }

    nlohmann::json configFile = nlohmann::json::parse(ifs);

    startingBudget = initalisedBudget;
    scalingFactor = configFile["WaveSettings"]["ScalingFactor"].get<int>();

    ifs.close();
}

void WaveManager::generateWave(Player& player) {

    while (allocatedBudget > 0) {
        const EnemyClassInfo affordedEnemy = getHighestEnemy(allocatedBudget);

        if (affordedEnemy.eType == Unassigned) { break; }

        currentWave.push_back(affordedEnemy.eType);
        allocatedBudget -= affordedEnemy.Cost;
        std::cout << "gen wave : " << affordedEnemy.Cost << std::endl;
    }

    const auto enemyCount {currentWave.size()};

    float iterator {0};

    for (auto &enemy : currentWave ) {
        iterator++;
        auto angle = 2.f * PI * iterator / enemyCount;
        sf::Vector2f spawnPosition {player.getPosition().x + std::cos(angle) * waveSpawnRadius, player.getPosition().y + std::sin(angle) * waveSpawnRadius};

        switch (enemy) {
            case Melee: {
                allEnemies.push_back(std::make_unique<MeleeEnemy>(spawnPosition, player));
                break;
            }

            case Ranged: {
                allEnemies.push_back(std::make_unique<RangedEnemy>(spawnPosition, player));
                break;
            }

            case Unassigned: {
                std::cerr << "Unassigned Enemy in WaveManager - skipping!" << std::endl;
                break;
            }
            default: ;
        }


    }
}

EnemyClassInfo WaveManager::getHighestEnemy(const int budget) {

    std::cout << "Dictionary size: " << enemyInfoDictionary.size() << " | Budget: " << budget << std::endl;

    EnemyClassInfo affordableEnemy {Unassigned, 0, 0};

    for (const auto& enemyClass : enemyInfoDictionary) {
        if (enemyClass.Cost <= budget && enemyClass.Cost > affordableEnemy.Cost) {
            affordableEnemy = enemyClass;
        }
    }

    return affordableEnemy;
}

void WaveManager::incrementBudget(const int wave) {
    allocatedBudget = startingBudget + (wave - 1) * scalingFactor;
}
