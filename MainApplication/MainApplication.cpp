//
// Created by Luca Schmitt on 07.08.24.
//

 #include "../Settings/Settings.h"
#include "MainApplication.h"

MainApplication::MainApplication(sf::RenderWindow& window) : sw::Application(window), dataset_(100, 16) {
    // Initialize the font to make it accessible throughout the project
    Settings::loadFont(Fonts::SourceCodeProLight);
    Settings::loadBoldFont(Fonts::SourceCodeProBold);

    // Set the dark mode boolean to initialize the colorspace
    Settings::setDarkMode(true);
}

void MainApplication::createSorters(const std::vector<std::string>& sorterNameList) {
    for (const auto& sorterName: sorterNameList) {
        if (sorterName == "Bubble sort") {
            // BubbleSorter bubbleSorter(dataset_<T>);
        }
    }
}

void MainApplication::setDataset(size_t size, u_int8_t diversity) {

}

