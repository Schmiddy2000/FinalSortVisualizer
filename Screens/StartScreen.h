//
// Created by Luca Schmitt on 09.08.24.
//

#ifndef FINALSORTVISUALIZER_STARTSCREEN_H
#define FINALSORTVISUALIZER_STARTSCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../SwiftifySFML/Screen.h"
#include "../SwiftifySFML/Application.h"
#include "../UIComponents/UIComponents.h"

class StartScreen: public sw::Screen {
public:
    // Constructor
    StartScreen(std::string name, sf::RenderWindow& window);

    // Transition to the next screen
    void transitionToSecondScreen();

    // Initialize all components of the start screen
    void initializeScreen();

    // Do one sorting step
    void stepSort();

    // Callback function for the button to execute one sorting step
    void stepSortCallback();

private:
    // Dataset visualizer instance that can be handled by this screen class instance
    //DatasetVisualizer datasetVisualizer_;

    // Rather add a dataset here
};

#endif //FINALSORTVISUALIZER_STARTSCREEN_H
