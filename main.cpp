#include <SFML/Graphics.hpp>
#include <vector>

#include "Settings/Settings.h"
#include "Screens/StartScreen.h"
#include "UIComponents/UIComponents.h"
#include "Sorter/Sorter.h"
#include "MainApplication/MainApplication.h"

/*
 * Observations:
 * - Alignment seems to pretty much work, except for the fact that the text box size doesn't seem to be
 * taken into account.
 * - The position where the center of the text should be rather seems to be the top-left corner.
 * - The small text offset also seems to need to be taken into account as it might not be included in
 * the local bounds.
 */


int main() {
    // Settings settings;

//    // Initialize the font to make it accessible throughout the project
//    Settings::loadFont(Fonts::SourceCodeProLight);
//    Settings::loadBoldFont(Fonts::SourceCodeProBold);
//
//    // Set the dark mode boolean to initialize the colorspace
//    Settings::setDarkMode(true);

    sf::RenderWindow window(sf::VideoMode(800, 600), "UI Demo");
    window.setFramerateLimit(10);

    auto myApp = std::make_shared<MainApplication>(window);
    Settings::setAppPointer(myApp);

    auto myScreen = std::make_shared<StartScreen>("StartScreen", window);
    myScreen->setBackground(sf::Color::Blue);
    myScreen->setLayoutOrientation(sw::LayoutOrientation::Stacked);
    myScreen->setSpacingProportions(sf::Vector2f(0.05, 0.05));
    myScreen->setAlignment(sw::Alignment::Center);
    myScreen->setPaddingProportions(sf::Vector2f(0.05, 0.05));

    auto otherScreen = std::make_shared<sw::Screen>("SecondScreen", window);

    // Create a container to see the offset more easily
    sw::Container myContainer("Container1", sf::Vector2f(0.25, 0.25));
    //myContainer.setBackground(sf::Color::Black);
    myContainer.setLayoutOrientation(sw::LayoutOrientation::Vertical);
    myContainer.setAlignment(sw::Alignment::Leading);

    // Create and add a Text element
    Text myText("Text1", sf::Vector2f(0.25, 0.25), "Hello, World!");
    // Text myText2("Text2", sf::Vector2f(0.25, 0.25), "Penis");

    myScreen->addContainer(std::make_unique<sw::Container>(std::move(myContainer)));

    myScreen->addUIComponent(std::make_unique<Text>(std::move(myText)));
    // myScreen->addUIComponent(std::make_unique<Text>(std::move(myText2)));

    // myScreen->addUIComponent(std::make_unique<Text>(std::move(myText)));
    //myScreen->addUIComponent(std::make_unique<Text>(std::move(myText2)));
    // myScreen->addContainer(std::make_unique<sw::Container>(std::move(myContainer)));

    // Add the screen to the application
    myApp->addScreen(std::move(myScreen));
    myApp->addScreen(std::move(otherScreen));

    myApp->run();

    return 0;
}


//    DatasetVisualizer dataVisualizer("dataVisualizer", sf::Vector2f(0.8, 0.6));
//    std::vector<float> myVec = {0.6, 0.7, 0.8, 0.9, 0.3, 0.5, 0.6, 0.4, 0.6};
//
//    dataVisualizer.setParentSize(static_cast<sf::Vector2f>(window.getSize()));
//    dataVisualizer.setupUIElements(myVec);
//    myScreen->addUIComponent(std::make_unique<DatasetVisualizer>(std::move(dataVisualizer)));
//
//    Button myButton("Button1", sf::Vector2f(0.25, 0.1), "Click to sort");
//    myButton.setBackgroundColor(sf::Color::White);
//    myScreen->addUIComponent(std::make_unique<Button>(std::move(myButton)));
