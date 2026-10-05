#include "GameHandler.h"
#include "ProjectileManager.h"

void GameHandler::tick(const float dt) {
    window.setView(player.getPlayerView());
    window.clear(sf::Color::Black);
    window.draw(mapSprite); // Draw the map lowest

    player.update(dt, window);
    player.draw(window); // Draw the player + gun
}

GameHandler::GameHandler(Player& playerRef, sf::RenderWindow& windowRef, sf::Sprite& mapSpriteRef) : player(playerRef), window(windowRef), mapSprite(mapSpriteRef) {

}