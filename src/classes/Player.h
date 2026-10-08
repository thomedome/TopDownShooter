#ifndef TOPDOWNSHOOTER_PLAYER_H
#define TOPDOWNSHOOTER_PLAYER_H

#include "Entity.h"
#include "enums.h"
#include "Weapon.h"
#include "common.h"

class Player : public Entity {
public:
    PlayerState getPlayerState() const;

    explicit Player(sf::Vector2f spawnPosition);

    void update(float dt, const sf::RenderWindow &window);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getMousePosition() const;
    sf::Vector2f getPosition() const;
    sf::View& getPlayerView();
    Weapon& getWeapon();
    void takeDamage(int damage) override;

private:
    sf::Vector2f mousePos;
    Weapon heldWeapon;
    PlayerState playerState {Stationary};
    sf::View playerView{mapPosition, {windowHeight * aspectRatio, windowHeight}};
    sf::RectangleShape objOnScreen {sf::Vector2f(50, 50)};
};

#endif //TOPDOWNSHOOTER_PLAYER_H