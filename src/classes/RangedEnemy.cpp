//
// Created by 30264651 on 12/10/2026.
//

#include "RangedEnemy.h"
#include "common.h"

void RangedEnemy::loadRangedStats(const nlohmann::json& json) {
    const std::string eName = to_string(enemyType);
    bufferRange = json[eName]["BufferRange"];
    retreatRange = attackRange / 3;
}
