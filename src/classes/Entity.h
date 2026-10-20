
#ifndef TOPDOWNSHOOTER_ENTITY_H
#define TOPDOWNSHOOTER_ENTITY_H

#include <string>
#include "SFML/Graphics.hpp"
#include "healthbar.h"

// Entity is the core class for any object that is alive and can move around, has HP etc.
// For now, sprite initialisation will belong to the child classes as I don't have sprites for characters yet. sf::RectangleShape assemble!

namespace Team {
    enum Team {
        Player,
        Enemy
    };
}

class Entity {
public:
    // Helper Functions
    [[nodiscard]] int getHealth() const;
    [[nodiscard]] int getMaxHealth() const;
    std::string getName();
    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] sf::Vector2i getSpatialCell() const;
    [[nodiscard]] sf::Vector2i getMapTile() const;
    [[nodiscard]] sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    virtual void takeDamage(int damage);
    bool isInvincible();
    float getMoveSpeed();
    void move(const sf::Vector2f pos);
    Team::Team getTeam() const;

protected:
    float invinciblityTimer {0.0f};
    bool invincible {false};
    float moveSpeed {250.f};
    sf::Vector2f mapPosition {};
    sf::Vector2i spatialCell{};
    sf::Vector2i mapTile{};
    int health {100};
    int maxHealth {100};
    std::string name {};
    healthbar healthBar {*this};
    Team::Team entityTeam {};
};

#endif //TOPDOWNSHOOTER_ENTITY_H