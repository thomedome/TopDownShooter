//
// Created by win11 on 10/10/2026.
//

#include "../../Button.h"

void Button::update(float dt) {

}

Button::Button(sf::Vector2f position, sf::Vector2f size) : location{position}, size{size} {

}


sf::Vector2f Button::getLocation() {
    return location;
}

bool Button::isClicked(sf::Vector2f mPos) {
    return objOnScreen.getGlobalBounds().contains(mPos);
}

void Button::onClick() {

}

void Button::onHover() {

}

void Button::draw(sf::RenderWindow& window) {
    window.draw(objOnScreen);
}