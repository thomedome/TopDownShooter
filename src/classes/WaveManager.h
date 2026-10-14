//
// Created by win11 on 14/10/2026.
//

#ifndef TOPDOWNSHOOTER_WAVEMANAGER_H
#define TOPDOWNSHOOTER_WAVEMANAGER_H

#include "Enemy.h"
#include "EnemyTypes.h"

struct EnemyClassInfo {
    EnemyType eType;
    unsigned int Cost {};
    unsigned int waveUnlocked {};
};

class WaveManager {
    public:
    void generateWave();

    WaveManager(const int initalisedBudget);

    private:

    std::vector<EnemyClassInfo> enemyInfoDictionary;

    std::vector<EnemyClassInfo> currentWave;
    int allocatedBudget {};

};


#endif //TOPDOWNSHOOTER_WAVEMANAGER_H