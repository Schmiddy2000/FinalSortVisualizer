//
// Created by Luca Schmitt on 07.08.24.
//

#include <iostream>

#include "StartScreen.h"
#include "../SwiftifySFML/Application.h"
#include "../SwiftifySFML/Screen.h"
#include "../Settings/Settings.h"

StartScreen::StartScreen(std::string name, sf::RenderWindow& window) : sw::Screen(std::move(name), window) {}

void StartScreen::transitionToSecondScreen() {
    if (Settings::appPointer) {
        (*Settings::appPointer).transitionToScreen("SecondScreen");
    } else {
        std::cerr << "No application set for screen '" << name_ << "'" << std::endl;
    }
}

void StartScreen::initializeScreen() {
    // Set up the screen's layout parameters
    setLayoutOrientation(sw::LayoutOrientation::Vertical);
    setAlignment(sw::Alignment::Center);
    setPaddingProportions(sf::Vector2f(0.05, 0.05));
    setSpacingProportions(sf::Vector2f(0.1, 0.1));
}

void StartScreen::stepSort() {
    if (Settings::appPointer) {

    }
}
