
#ifndef TOPDOWNSHOOTER_ENTITY_H
#define TOPDOWNSHOOTER_ENTITY_H

#include <string>
#include "SFML/Graphics.hpp"

// Entity is the core class for any object that is alive and can move around, has HP etc.
// For now, sprite initialisation will belong to the child classes as I don't have sprites for characters yet. sf::RectangleShape assemble!

class Entity {
public:
    // Helper Functions
    [[nodiscard]] int getHealth() const;
    std::string getName();
    [[nodiscard]] bool isAlive() const;

protected:
    float moveSpeed {250.f};
    sf::Vector2f mapPosition {};
    int health {};
    int maxHealth {};
    std::string name {};
};

#endif //TOPDOWNSHOOTER_ENTITY_H