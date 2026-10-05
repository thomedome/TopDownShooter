#ifndef TOPDOWNSHOOTER_PLAYER_H
#define TOPDOWNSHOOTER_PLAYER_H

#include "Entity.h"
#include "enums.h"
#include "Weapon.h"

class Player : public Entity {
public:
    PlayerState getPlayerState() const;

    Player(sf::Vector2f spawnPosition);

    void update(float dt, const sf::RenderWindow &window);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getMousePosition() const;
    sf::Vector2f getPosition() const;
    sf::View& getPlayerView();
    Weapon& getWeapon();

private:
    sf::Vector2f mousePos;
    Weapon heldWeapon;
    PlayerState playerState {Stationary};
    sf::View playerView{mapPosition, {750, 750}};
    sf::RectangleShape objOnScreen {sf::Vector2f(50, 50)};
};

// std::vector<Bullet> ownedBullets; NEEDS TO BE MOVED TO GAMEHANDLER


#endif //TOPDOWNSHOOTER_PLAYER_H