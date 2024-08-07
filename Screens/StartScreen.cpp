//
// Created by Luca Schmitt on 07.08.24.
//

#include <iostream>

#include "../SwiftifySFML/Screen.h"
#include "../SwiftifySFML/Application.h"

class StartScreen: public sw::Screen {
public:
    StartScreen(std::string name, sf::RenderWindow& window) : sw::Screen(std::move(name), window) {}
    void transitionToSecondScreen() {
        if (app_) {
            (*app_).transitionToScreen("SecondScreen");
        } else {
            std::cerr << "No application set for screen '" << name_ << "'" << std::endl;
        }
    }

    void createContainers() {

    }
};
