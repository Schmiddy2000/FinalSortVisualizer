//
// Created by Luca Schmitt on 07.08.24.
//
#include "UIComponents.h"
#include "../Settings/Settings.h"
#include <string>
#include <SFML/Graphics.hpp>

// --- Button ---

// ___________________________________________________________________________
Button::Button(std::string name, sf::Vector2f sizeProportions, std::string label)
: sw::UIComponent(std::move(name), sizeProportions), label_(std::move(label)) {}


// ___________________________________________________________________________
void Button::draw(sf::RenderWindow &window) {
    // Update render information if needed
    if (needRenderUpdate_) {
        computeRenderInformation();
    }

    window.draw(buttonShape_);
    window.draw(buttonLabel_);
}


// ___________________________________________________________________________
bool Button::handleEvent(const sf::Event &event) {
    // Flag to indicate to the parent container if the event still might need to be handled
    bool hasBeenHandled = false;

    // Check the type of event and location in case of a mouse event.
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (containsPosition(mousePos)) {
            // Handle event if a callback is set

            if (callback_) {
                hasBeenHandled = true;
                callback_();
            }
        }
    }

    // Return this component's handle status
    return hasBeenHandled;
}


// ___________________________________________________________________________
// Maybe use the Text class here as well
// ___________________________________________________________________________
void Button::computeRenderInformation() {
    buttonShape_.setSize(size_);
    buttonShape_.setPosition(position_);
    buttonShape_.setFillColor(backgroundColor_);

    buttonLabel_.setFont(Settings::boldFont);
    buttonLabel_.setString(label_);
    buttonLabel_.setCharacterSize(FontSize::Large);
    buttonLabel_.setFillColor(foregroundColor_);
    buttonLabel_.setPosition(position_);

    // Reset the render update flag
    needRenderUpdate_ = false;
}


// --- Text ---

// ___________________________________________________________________________
Text::Text(std::string name, sf::Vector2f sizeProportions, std::string content)
: sw::UIComponent(std::move(name), sizeProportions) {
    content_ = std::move(content);

    // Set default values
    fontSize_ = FontSize::Large;
    bold_ = false;
    needRenderUpdate_ = true;
}

// ___________________________________________________________________________
void Text::draw(sf::RenderWindow &window) {
    // Update render information if needed
    if (needRenderUpdate_) {
        computeRenderInformation();
    }

    window.draw(text_);
}

// ___________________________________________________________________________
bool Text::handleEvent(const sf::Event &event) {
    // Flag to indicate to the parent container if the event still might need to be handled
    bool hasBeenHandled = false;

    // Check the type of event and location in case of a mouse event.
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (containsPosition(mousePos)) {
            // Handle event if a callback is set

            if (callback_) {
                hasBeenHandled = true;
                callback_();
            }
        }
    }

    // Return this component's handle status
    return hasBeenHandled;
}

// ___________________________________________________________________________
void Text::computeRenderInformation() {
    // Set up the text properties
    text_.setPosition(position_);
    text_.setCharacterSize(fontSize_);
    text_.setString(content_);
    text_.setFillColor(ColorSpace::textForeground);

    if (bold_) {
        text_.setFont(Settings::boldFont);
    } else {
        text_.setFont(Settings::font);
    }

    // Reset render update flag
    needRenderUpdate_ = false;
}

void Text::setFontSize(int fontSize) {
    fontSize_ = fontSize;

    // Update render update flag
    needRenderUpdate_ = true;
}

void Text::setBold(bool bold) {
    bold_ = bold;

    // Update render update flag
    needRenderUpdate_ = true;
}

void Text::setContent(const std::string &content) {
    content_ = content;

    // Update render update flag
    needRenderUpdate_ = true;
}


// --- TextField ---

// ___________________________________________________________________________
TextField::TextField(std::string name, sf::Vector2f sizeProportions, std::string content)
        : UIComponent(std::move(name), sizeProportions) {
    content_ = std::move(content);

    // Set default values
    multiLine_ = true;
    fontSize_ = FontSize::Medium;
    bold_ = false;
    alignment_ = sw::Alignment::Center;

    needRenderUpdate_ = true;
}

// ___________________________________________________________________________
float TextField::contentToTextLines() {
    return 0;
}


// ___________________________________________________________________________
sf::Vector2f TextField::getRealSize() {
    return sf::Vector2f();
}


// ___________________________________________________________________________
void TextField::draw(sf::RenderWindow &window) {
    for (auto& line: textLines_) {
        window.draw(line);
    }
}


// ___________________________________________________________________________
bool TextField::handleEvent(const sf::Event &event) {
    // Flag to indicate to the parent container if the event still might need to be handled
    bool hasBeenHandled = false;

    // Check the type of event and location in case of a mouse event.
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (containsPosition(mousePos)) {
            // Handle event if a callback is set

            if (callback_) {
                hasBeenHandled = true;
                callback_();
            }
        }
    }

    // Return this component's handle status
    return hasBeenHandled;
}


// ___________________________________________________________________________
void TextField::computeRenderInformation() {

}

std::vector<std::string> TextField::splitString(const std::string &str, char delimiter) {
    return std::vector<std::string>();
}


// --- Slider ---

Slider::Slider(std::string name, const sf::Vector2f sizeProportions, int minValue, int maxValue)
: UIComponent(std::move(name), sizeProportions) {
    minValue_ = minValue;
    maxValue_ = maxValue;
    currentValue_ = static_cast<int>((maxValue_ - minValue_) / 2);
}

// ___________________________________________________________________________
void Slider::draw(sf::RenderWindow &window) {

}


// ___________________________________________________________________________
bool Slider::handleEvent(const sf::Event &event) {

}


// ___________________________________________________________________________
void Slider::computeRenderInformation() {

}


// ___________________________________________________________________________
void Slider::updateRenderInstructions() {

}
