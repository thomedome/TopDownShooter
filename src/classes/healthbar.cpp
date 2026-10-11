//
// Created by win11 on 11/10/2026.
//

#include "healthbar.h"
#include <algorithm>

void healthbar::update(sf::Vector2f entityPosition, float currentHealth, float maxHealth) {
    float decimal = currentHealth / maxHealth;

    decimal = std::clamp(decimal, 0.f, 1.f);

    healthBarFill.setSize({50.f * decimal, 10.f});

    if (decimal >= .66) {
        healthBarFill.setFillColor(sf::Color::Green);
    } else if (decimal >= .33 && decimal < .66) {
        healthBarFill.setFillColor(sf::Color::Yellow);
    } else {
        healthBarFill.setFillColor(sf::Color::Red);
    }

    sf::Vector2f newPosition {entityPosition.x, (entityPosition.y - 35.f)};

    healthBarFill.setPosition(newPosition);
    healthBarBG.setPosition(newPosition);
}

void healthbar::draw(sf::RenderWindow &window) {
    window.draw(healthBarBG);
    window.draw(healthBarFill);
}


healthbar::healthbar(Entity& parent) : Parent(parent) {
    healthBarBG.setOutlineColor(sf::Color::White);
    healthBarBG.setFillColor(Colours::darkRed);
    healthBarBG.setOrigin({healthBarBG.getSize().x / 2, healthBarBG.getSize().y / 2});
    healthBarFill.setOrigin({healthBarFill.getSize().x / 2, healthBarFill.getSize().y / 2});
}