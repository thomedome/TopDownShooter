//
// Created by win11 on 14/10/2026.
//

#ifndef TOPDOWNSHOOTER_WAVEMANAGER_H
#define TOPDOWNSHOOTER_WAVEMANAGER_H

#include "Enemy.h"
#include "EnemyTypes.h"

struct EnemyClassInfo {
    EnemyType eType;
    int Cost {};
    unsigned int waveUnlocked {};
};

// Just a prototype - will refactor to fill on runtime when working
struct EnemyDict {
    EnemyClassInfo MeleeEnemy {Melee, 1, 1};
    EnemyClassInfo RangedEnemy {Ranged, 3, 3};
};

class WaveManager {
    public:
    void generateWave(Player& player);

    WaveManager(const int initalisedBudget);

    std::vector<std::unique_ptr<Enemy>> allEnemies;

    void incrementBudget(const int wave);

    private:
    EnemyClassInfo getHighestEnemy(const int budget);

    std::vector<EnemyClassInfo> enemyInfoDictionary {
        {Melee, 1, 1},
        {Ranged, 3, 3}
    };

    std::vector<EnemyType> currentWave;
    int allocatedBudget {};

    int startingBudget {};
    int scalingFactor {};

};


#endif //TOPDOWNSHOOTER_WAVEMANAGER_H