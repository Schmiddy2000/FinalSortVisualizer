//
// Created by Luca Schmitt on 07.08.24.
//

#include <iostream>

#include "StartScreen.h"
#include "../MainApplication/MainApplication.h"
#include "../SwiftifySFML/Screen.h"
#include "../Settings/Settings.h"

StartScreen::StartScreen(std::string name, sf::RenderWindow& window)
: sw::Screen(std::move(name), window), datasetVisualizer_("DatasetVisualizer", sf::Vector2f(0.5, 0.5)) {
    // Since the app_ parameter is of type sw::Application, this only grants access to the functions defined
    // in the base class
    app_ = Settings::appPointer;

    // Set up the dataset visualizer
    datasetVisualizer_.setParentSize(static_cast<sf::Vector2f>(window.getSize()));
    datasetVisualizer_.setupUIElements(Settings::appPointer->getDataset().getNormalizedData());
    initializeScreen();
}

void StartScreen::transitionToSecondScreen() {
    if (Settings::appPointer) {
        (*Settings::appPointer).transitionToScreen("SecondScreen");
    } else {
        std::cerr << "No application set in settings" << std::endl;
    }
}

void StartScreen::initializeScreen() {
    // Set up the screen's layout parameters
    setLayoutOrientation(sw::LayoutOrientation::Vertical);
    setAlignment(sw::Alignment::Center);
    setPaddingProportions(sf::Vector2f(0.05, 0.05));
    setSpacingProportions(sf::Vector2f(0.1, 0.1));

    addUIComponent(std::make_unique<DatasetVisualizer>(std::move(datasetVisualizer_)));

    Button stepSortButton("StepSortButton", sf::Vector2f(0.3, 0.1), "Sort one step");
    stepSortButton.setBackgroundColor(sf::Color::Blue);
    stepSortButton.setCallback([this]() {
        this->stepSortCallback();
    });

    Button selectDatasetButton("selectDatasetButton", sf::Vector2f(0.3, 0.1), "Select dataset");
    selectDatasetButton.setBackgroundColor(sf::Color::Blue);
    selectDatasetButton.setCallback([]() {
        Settings::appPointer->createSorters(std::vector<std::string>{std::string("Bubble sort")});
    });

    addUIComponent(std::make_unique<Button>(std::move(stepSortButton)));
    addUIComponent(std::make_unique<Button>(std::move(selectDatasetButton)));
}


// The issue is that in this function, the vectors of DatasetVisualizer that store the rectangles and heights are empty.
void StartScreen::stepSort() {
    if (Settings::appPointer) {
        // Get a reference to the vector of sorter instances
        auto& sorters = Settings::appPointer->getSorters();

        std::cout << "Got sorters" << std::endl;

        // For each sorter, call its sort method if it's dataset isn't already sorted
        for (auto& sorter: sorters) {
            if (!sorter->isSorted()) {
                // Get the indices that should be swapped
                auto swapIndices = sorter->stepSort(false);

                std::cout << "Indices:" << swapIndices.first << ", " << swapIndices.second << std::endl;

                // Update the related components
                if (swapIndices != std::pair<size_t, size_t>(0, 0)) {
                    datasetVisualizer_.swapDataBars(swapIndices.first, swapIndices.second);
                }
            }
        }
    }
}

void StartScreen::stepSortCallback() {
    // This is kind of dumb, but probably needed since the functions are being moved when set as a callback.
    // Since they only take up 24 bytes, this should be changed.
    std::cout << "did swap" << std::endl;
    stepSort();
}
