//
// Created by Luca Schmitt on 07.08.24.
//
#include "UIComponents.h"
#include <string>
#include <SFML/Graphics.hpp>

// --- Button ---

Button::Button(std::string name, sf::Vector2f sizeProportions, std::string label)
: sw::UIComponent(std::move(name), sizeProportions) {

}

void Button::draw(sf::RenderWindow &window) {

}

bool Button::handleEvent(const sf::Event &event) {

}

void Button::computeRenderInformation() {

}

// --- TextField ---



TextField::TextField(std::string name, const sf::Vector2f sizeProportions, sf::Vector2f position, sf::Vector2f size,
                     std::string content, int fontSize, bool bold, sw::Alignment alignment, bool multiLine)
        : UIComponent(name, sizeProportions) {

}

float TextField::contentToTextLines() {
    return 0;
}

sf::Vector2f TextField::getRealSize() {
    return sf::Vector2f();
}

void TextField::draw(sf::RenderWindow &window) {

}

bool TextField::handleEvent(const sf::Event &event) {

}

void TextField::computeRenderInformation() {

}


// --- Slider ---



void Slider::draw(sf::RenderWindow &window) {

}

bool Slider::handleEvent(const sf::Event &event) {

}

void Slider::computeRenderInformation() {

}

void Slider::updateRenderInstructions() {

}
