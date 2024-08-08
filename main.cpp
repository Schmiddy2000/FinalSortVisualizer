#include <iostream>
#include <SFML/Graphics.hpp>

//#include "../SwiftifySFML/Container.h"
//#include "../SwiftifySFML/Application.h"
//#include "../SwiftifySFML/Screen.h"
//#include "../SwiftifySFML/Enumerations.h"

#include "Settings/Settings.h"
#include "Screens/StartScreen.cpp"
#include "MainApplication/MainApplication.h"
#include "UIComponents/UIComponents.h"


int main() {
    Settings settings;

    // Initialize the font to make it accessible throughout the project
    Settings::loadFont(Fonts::SourceCodeProLight);
    Settings::loadBoldFont(Fonts::SourceCodeProBold);

    // Set the dark mode boolean to initialize the colorspace
    Settings::setDarkMode(true);

    sf::RenderWindow window(sf::VideoMode(800, 600), "UI Demo");
    window.setFramerateLimit(10);

    auto myApp = std::make_shared<sw::Application>(window);

    auto myScreen = std::make_shared<StartScreen>("StartScreen", window);
    myScreen->setBackground(sf::Color::Blue);
    myScreen->setLayoutOrientation(sw::LayoutOrientation::Vertical);
    myScreen->setSpacingProportions(sf::Vector2f(0, 0.05));
    myScreen->setAlignment(sw::Alignment::Top);

    auto otherScreen = std::make_shared<sw::Screen>("SecondScreen", window);

    Text myText("Text1", sf::Vector2f(0.1, 0.1), "Press me");
    myText.setForegroundColor(ColorSpace::buttonForeground);
    myScreen->addUIComponent(std::make_unique<Text>(std::move(myText)));

//    sw::Container myContainer("Container1", sf::Vector2f(0.5, 0.5));
//    myContainer.setBackground(sf::Color::Black);
//    myScreen->addContainer(std::make_unique<sw::Container>(std::move(myContainer)));

    // Add the screen to the application
    myApp->addScreen(std::move(myScreen));
    myApp->addScreen(std::move(otherScreen));

    myApp->run();

    return 0;
}



//int main() {
//    Settings settings;
//
//    // Set the pointer to this MainApplication instance in the Settings
//    // Settings::setAppPointer(this);
//
//    // Initialize the font to make it accessible throughout the project
//    Settings::loadFont(Fonts::SourceCodeProLight);
//    Settings::loadBoldFont(Fonts::SourceCodeProBold);
//
//    // Set the dark mode boolean to initialize the colorspace
//    Settings::setDarkMode(true);
//
//    sf::RenderWindow window(sf::VideoMode(800, 600), "UI Demo");
//    window.setFramerateLimit(10);
//
//    auto myApp = std::make_shared<sw::Application>(window);
//
//    auto myScreen = std::make_shared<StartScreen>("StartScreen", window);
//    myScreen->setBackground(sf::Color::Blue);
//    myScreen->setLayoutOrientation(sw::LayoutOrientation::Vertical);
//    myScreen->setSpacingProportions(sf::Vector2f(0, 0.05));
//
//    auto otherScreen = std::make_shared<sw::Screen>("SecondScreen", window);
//
//    sw::Container myContainer("Container1", sf::Vector2f(0.2, 0.2));
//    myContainer.setBackground(ColorSpace::buttonBackground);
//    myContainer.setAlignment(sw::Alignment::BottomTrailing);
//
//    Text myText("Text1", sf::Vector2f(1, 1), "Press me");
//    myText.setForegroundColor(ColorSpace::buttonForeground);
//    myContainer.addUIComponent(std::make_unique<Text>(std::move(myText)));
//
//    // Capture myScreen using a shared_ptr in the lambda
//    myContainer.setCallback([myScreen]() {
//        std::cout << "Setting function" << std::endl;
//        myScreen->transitionToSecondScreen();
//    });
//
//    sw::Container mySecondContainer("Container2", sf::Vector2f(0.35, 0.2));
//    mySecondContainer.setBackground(sf::Color::Green);
//
//    Button myButton("myButton", sf::Vector2f(0.3, 0.1), "Hey man");
//    myButton.setForegroundColor(sf::Color::Black);
//    myButton.setBackgroundColor(sf::Color::Magenta);
//
//    myScreen->addContainer(std::make_unique<sw::Container>(std::move(myContainer)));
//    myScreen->addContainer(std::make_unique<sw::Container>(std::move(mySecondContainer)));
//    myScreen->addUIComponent(std::make_unique<Button>(std::move(myButton)));
//
////    sw::Container buttonContainer("MyButton", sf::Vector2f(0.4, 0.2));
////    buttonContainer.setBackground(sf::Color::Red);
//
//    // Add the screen to the application
//    myApp->addScreen(std::move(myScreen));
//    myApp->addScreen(std::move(otherScreen));
//
//    myApp->run();
//
//    return 0;
//}

//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "UI Demo");
//    // Set the frame rate limit to x FPS
//    window.setFramerateLimit(10);
//
//    // Ensure that the Application is created as a shared_ptr
//    auto myApp = std::make_shared<sw::Application>(window);
//
//    // Create a screen and set a background color
//    StartScreen myScreen("StartScreen", window);
//    myScreen.setBackground(sf::Color::Blue);
//
//    sw::Screen otherScreen("SecondScreen", window);
//
//    // Create and add a container
//    sw::Container myContainer("Container1", sf::Vector2f(0.5, 0.5));
//    myContainer.setBackground(sf::Color::Magenta);
//
//    // Set the callback using a lambda function
//    myContainer.setCallback([&myScreen]() {
//        std::cout << "Setting function" << std::endl;
//        myScreen.transitionToSecondScreen();
//    });
//
//    myScreen.addContainer(std::make_unique<sw::Container>(std::move(myContainer)));
//
//    sw::Container buttonContainer("MyButton", sf::Vector2f(0.4, 0.2));
//    buttonContainer.setBackground(sf::Color::Red);
//
////    // Add the screen to the application
////    myApp->addScreen(std::make_unique<sw::Screen>(std::move(myScreen)));
////    myApp->addScreen(std::make_unique<sw::Screen>(std::move(otherScreen)));
//
//// Add the screen to the application
//    // Make sure to add myScreen by reference to avoid invalidating the lambda capture
//    auto screenPtr = std::make_unique<sw::Screen>(std::move(myScreen));
//    myApp->addScreen(std::move(screenPtr));
//    myApp->addScreen(std::make_unique<sw::Screen>(std::move(otherScreen)));
//
//    // Run the application
//    myApp->run();
//
//    return 0;
//}