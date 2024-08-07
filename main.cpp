#include <iostream>
#include <SFML/Graphics.hpp>

#include "../SwiftifySFML/Container.h"
#include "../SwiftifySFML/Application.h"
#include "../SwiftifySFML/Screen.h"
#include "../SwiftifySFML/Enumerations.h"

#include "Settings/Settings.h"
#include "Screens/StartScreen.cpp"
#include "MainApplication/MainApplication.h"

int main() {
    Settings settings;

    sf::RenderWindow window(sf::VideoMode(800, 600), "UI Demo");
    window.setFramerateLimit(10);

    auto myApp = std::make_shared<sw::Application>(window);

    auto myScreen = std::make_shared<StartScreen>("StartScreen", window);
    myScreen->setBackground(sf::Color::Blue);
    myScreen->setLayoutOrientation(sw::LayoutOrientation::Vertical);
    myScreen->setSpacingProportions(sf::Vector2f(0, 0.05));

    auto otherScreen = std::make_shared<sw::Screen>("SecondScreen", window);

    sw::Container myContainer("Container1", sf::Vector2f(0.5, 0.5));
    // myContainer.setBackground(sf::Color::Magenta);
    myContainer.setBackground(ColorSpace::buttonBackground);

    // Capture myScreen using a shared_ptr in the lambda
    myContainer.setCallback([myScreen]() {
        std::cout << "Setting function" << std::endl;
        myScreen->transitionToSecondScreen();
    });

    sw::Container mySecondContainer("Container2", sf::Vector2f(0.35, 0.2));

    myScreen->addContainer(std::make_unique<sw::Container>(std::move(myContainer)));
    myScreen->addContainer(std::make_unique<sw::Container>(std::move(mySecondContainer)));

    sw::Container buttonContainer("MyButton", sf::Vector2f(0.4, 0.2));
    buttonContainer.setBackground(sf::Color::Red);

    // Add the screen to the application
    myApp->addScreen(std::move(myScreen));
    myApp->addScreen(std::move(otherScreen));

    myApp->run();

    return 0;
}

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