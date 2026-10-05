//
// Created by win11 on 05/10/2026.
//

#ifndef TOPDOWNSHOOTER_GAMEHANDLER_H
#define TOPDOWNSHOOTER_GAMEHANDLER_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ProjectileManager.h"

class GameHandler { // Used to hold what objects needs updating + rendering, and have an overarching tick method to update everything.

public:
    Player& player;
    // Enemies go here eventually...

    ProjectileManager& projectileManager{};
    sf::RenderWindow& window;
    bool showFPS {};
    void tick(float dt);

    GameHandler(Player &playerRef, sf::RenderWindow& windowRef);
};


#endif //TOPDOWNSHOOTER_GAMEHANDLER_H
