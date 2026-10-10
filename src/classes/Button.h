//
// Created by win11 on 10/10/2026.
//

#ifndef TOPDOWNSHOOTER_BUTTON_H
#define TOPDOWNSHOOTER_BUTTON_H

// ancestor class - might use for image button / text button etc...

#include "SFML/Graphics.hpp"

class Button {
    public:

    Button (sf::Vector2f position, sf::Vector2f size);

    sf::Vector2f getLocation();

    void update(float dt);

    void onClick();
    void onHover();
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2f mPos);
    bool isHover();

private:
    sf::Vector2f location {};
    sf::Vector2f size {};
    sf::RectangleShape objOnScreen {};
    bool isHovered {false};

};


#endif //TOPDOWNSHOOTER_BUTTON_H