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
    void Death();
    void takeDamage(int damage) override;
    void addScore(int addingScore);
    int getScore() const;

private:
    sf::Vector2f mousePos;
    Weapon heldWeapon;
    PlayerState playerState {Stationary};
    sf::View playerView{mapPosition, {windowHeight * aspectRatio, windowHeight}};
    sf::RectangleShape objOnScreen {sf::Vector2f(50, 50)};
    bool isDying {false};
    float deathTweenTime {0.0f};
    float deathTweenDuration {2.5f};
    int score{0};

    sf::Vector2f deathCamStartSize = getPlayerView().getSize();
    sf::Vector2f deathCamEndSize {deathCamStartSize.x + (300.f * aspectRatio), deathCamStartSize.y + 300.f};
};

#endif //TOPDOWNSHOOTER_PLAYER_H