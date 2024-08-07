//
// Created by Luca Schmitt on 07.08.24.
//

#ifndef FINALSORTVISUALIZER_SETTINGS_H
#define FINALSORTVISUALIZER_SETTINGS_H

#include "../SwiftifySFML/Enumerations.h"
#include "../SwiftifySFML/Application.h"

#include <SFML/Graphics.hpp>
#include <utility>
#include <iostream>
#include <memory>


/*
 * FontSize class. Contains predefined and descriptive values for font sizes.
 */
class FontSize {
public:
    static int Tiny;
    static int Small;
    static int Medium;
    static int Large;
    static int Huge;
};


/*
 * FontType enum. Provides a base to display different types of fonts, like regular, bold, italic, etc.
 *
 * Or is this redundant, and it'd be better to add a bool 'bold' where it might be needed?
 */
enum class FontType {
    Regular,
    Italic,
    Bold
};


// Doesn't work as intended due to font assignment... Maybe look into it (more user options and fewer settings-ref
// passes)
class Fonts {
public:
    // Regular fonts
    static std::string DejaVuSansMono;
    static std::string OpenSansRegular;
    static std::string PTSansNarrowRegular;
    static std::string RobotoRegular;
    static std::string SFPro;
    static std::string SourceCodeProRegular;

    // Light fonts
    static std::string RobotoLight;
    static std::string SourceCodeProLight;

    // Medium fonts
    static std::string RobotoMedium;

    // Bold fonts
    static std::string SourceCodeProBold;
};

/*
 * Base class for colors. Intended to basically work like an enum, but we can't subclass those.
 *
 * Need to add more colors (for all UI elements)...
 */
class ColorSpace {
public:
    static sf::Color buttonForeground;
    static sf::Color buttonBackground;
    static sf::Color textForeground;
    static sf::Color textBackground;

    static sf::Color screenBackground;
};

// Light mode colors
class LightModeColors : public ColorSpace {
public:
    static void initialize() {
        buttonForeground = sf::Color::Black;
        buttonBackground = sf::Color::Green;
        textForeground = sf::Color::Black;
        textBackground = sf::Color::White;

        screenBackground = sf::Color::White;
    }
};

// Dark mode colors
class DarkModeColors : public ColorSpace {
public:
    static void initialize() {
        buttonForeground = sf::Color::White;
        buttonBackground = sf::Color::Magenta;
        textForeground = sf::Color::White;
        textBackground = sf::Color::Black;

        screenBackground = sf::Color::Black;
    }
};


/*
 * Static settings class. Ensures accessibility throughout the project without the need to pass pointers or references.
 *
 * Thoughts:
 * - Can this contain a pointer to the MainApplication instance running the program? This would probably allow for
 * lambda functions to be added to UI components. This would eradicate the need for a response format by buttons and
 * could allow for locally defined interactions within the app.
 * - How complex could these functions be and would that be enough?
 * - Should the application pointer rather be a weak pointer?
 */
class Settings {
public:
    // Pointer to the MainApplication instance running the program.
    static std::shared_ptr<sw::Application> appPointer;

    // Set the appPointer. Called in the constructor of MainApplication using *this.
    static void setAppPointer(std::shared_ptr<sw::Application> appPtr) { appPointer = std::move(appPtr); }

    // Store screen dimensions.
    static std::pair<int, int> windowSize;

    // Set a new window size. Would have to trigger re-rendering.
    static void setWindowSize(std::pair<int, int> size) { windowSize = size; }

    // Dark mode
    static bool darkMode;

    // Set light or dark mode. Updates the colorspace.
    static void setDarkMode(bool mode) {
        darkMode = mode;

        if (darkMode) {
            DarkModeColors::initialize();
        } else {
            LightModeColors::initialize();
        }
    }

    // Frame rate of the app
    static u_int8_t frameRate;

    // Set the frame rate
    static void setFrameRate(u_int8_t rate) { frameRate = rate; }

    // Sorting speed of the sorting algorithms in steps per second.
    static float sortingSpeed;

    // Set the sorting speed
    static void setSortingSpeed(float speed) { sortingSpeed = speed; }

    // Stores the font for the app. Doesn't need to be changed.
    static sf::Font font;
    static sf::Font boldFont;

    // Set the font though a function in the MainApplication, since it can't be initialized in-line
    static bool loadFont(const std::string& filePath) {
        if (!font.loadFromFile(filePath)) {
            std::cerr << "Failed to load font from " << filePath << std::endl;
            return false;
        }
        return true;
    }

    static bool loadBoldFont(const std::string& filePath) {
        if (!boldFont.loadFromFile(filePath)) {
            std::cerr << "Failed to load font from " << filePath << std::endl;
            return false;
        }
        return true;
    }
};


#endif //FINALSORTVISUALIZER_SETTINGS_H
