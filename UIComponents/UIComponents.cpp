//
// Created by Luca Schmitt on 07.08.24.
//
#include "UIComponents.h"
#include "../Settings/Settings.h"

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

// --- Button ---

// ___________________________________________________________________________
Button::Button(std::string name, sf::Vector2f sizeProportions, std::string label)
: sw::UIComponent(std::move(name), sizeProportions), label_(std::move(label)) {
    needRenderUpdate_ = true;
}

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
// This class should be resized to only take up the space that the actual text box takes up.
// To do this:
// - Calculate the new size proportions from the size of the localBounds
// - Should the position also be updated accordingly?

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

    // std::cout << "Size_: " << size_.x << ", " << size_.y << std::endl;

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
    text_.setCharacterSize(fontSize_);
    text_.setString(content_);
    text_.setFillColor(ColorSpace::textForeground);
    text_.setFont(bold_ ? Settings::boldFont : Settings::font);

    // Adjust the position and possibly the size
    adjustPosition();
    computeSize();

    // The position should be updated afterward
    text_.setPosition(position_);

    // Reset render update flag
    needRenderUpdate_ = false;
}

// ___________________________________________________________________________
void Text::setFontSize(int fontSize) {
    fontSize_ = fontSize;

    // Update render update flag
    needRenderUpdate_ = true;
}

// ___________________________________________________________________________
void Text::setBold(bool bold) {
    bold_ = bold;

    // Update render update flag
    needRenderUpdate_ = true;
}

// ___________________________________________________________________________
void Text::setContent(const std::string &content) {
    content_ = content;

    // Update render update flag
    needRenderUpdate_ = true;
}

//const sf::Vector2f &Text::getSize() const {
//    sf::Vector2f realSize = text_.getLocalBounds().getSize();
//
//    return realSize;
//}

// ___________________________________________________________________________
void Text::adjustSize() {
    size_ = text_.getLocalBounds().getSize();
}

// ___________________________________________________________________________
void Text::adjustPosition() {

    // position_ = position_ - sf::Vector2f((parentSize_.x * sizeProportions_.x - size_.x) / 2, (parentSize_.y * sizeProportions_.y - size_.y) / 2);

//    // Check if the position needs to be updated
//
//    // Calculate the theoretically specified size
//    sf::Vector2f theoreticalSize(sizeProportions_.x * parentSize_.x, sizeProportions_.y * parentSize_.y);
//
//    // Calculate the buffer
//    sf::Vector2f actualSize = text_.getLocalBounds().getSize();
//    sf::Vector2f buffer((theoreticalSize.x - actualSize.x) / 2, (theoreticalSize.y - actualSize.y) / 2);
//
//    // Update the position
//    position_ += buffer;
}

// ___________________________________________________________________________
void Text::computeSize() {
    size_ = text_.getLocalBounds().getSize();
}


// --- TextField ---

// ___________________________________________________________________________
TextField::TextField(std::string name, sf::Vector2f sizeProportions, std::string content)
        : UIComponent(std::move(name), sizeProportions), container_("TextFieldRoot", sizeProportions) {
    content_ = std::move(content);

    // Set default values
    multiLine_ = true;
    fontSize_ = FontSize::Medium;
    bold_ = false;
    alignment_ = sw::Alignment::Center;

    needRenderUpdate_ = true;
}

// ___________________________________________________________________________
std::vector<std::string> TextField::splitString(const std::string &string, char delimiter) {
    // Create the vector to store the words
    std::vector<std::string> words;

    // Create the variable to store the current word
    std::string word;

    // Convert string to string stream to make use of std::getline.
    std::stringstream stringStream(string);

    // Add word to words
    while(std::getline(stringStream, word, delimiter)) {
        words.push_back(word);
    }

    return words;
}

// ___________________________________________________________________________
float TextField::contentToTextLines() {
    // Split the content string by space characters and check for every word, after appending it to the string
    // for the current line, if it exceeds size.x. If that's the case, create a textLine with the text that fits.

    // Variable to store the text for the current line.
    std::string currentString;

    // Create an instance of sf::Text to get the UI bound widths. Should / can this be outsourced to the
    // getRenderInstructions functions?
    sf::Text lineText;
    // Set the rest of the properties here as well
    lineText.setFont(bold_ ? Settings::boldFont : Settings::font);
    lineText.setCharacterSize(fontSize_);
    lineText.setFillColor(ColorSpace::textForeground);

    // Get the height for a new line character. Used to calculate the height of the supposed text box
    lineText.setString("\n");
    float newLineHeight = lineText.getLocalBounds().height;

    // Now split the content
    std::vector<std::string> splitContent = std::move(splitString(content_, ' '));
}

// ___________________________________________________________________________
sf::Vector2f TextField::getRealSize() {
    return sf::Vector2f();
}

// ___________________________________________________________________________
void TextField::draw(sf::RenderWindow &window) {
    for (auto& line: textLines_) {
        line.draw(window);
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

// ___________________________________________________________________________
void TextField::setMultiLine(bool multiLine) {
    if (multiLine_ != multiLine) {
        multiLine_ = multiLine;

        // Update render update flag
        needRenderUpdate_ = true;
    }
}

// ___________________________________________________________________________
void TextField::setFontSize(int fontSize) {
    if (fontSize_ != fontSize) {
        fontSize_ = fontSize;

        // Update render update flag
        needRenderUpdate_ = true;
    }
}

// ___________________________________________________________________________
void TextField::setBold(bool bold) {
    if (bold_ != bold) {
        bold_ = bold;

        // Update render update flag
        needRenderUpdate_ = true;
    }
}

// ___________________________________________________________________________
void TextField::setAlignment(sw::Alignment alignment) {
    if (alignment_ != alignment) {
        alignment_ = alignment;

        // Update render update flag
        needRenderUpdate_ = true;
    }
}

// ___________________________________________________________________________
bool TextField::getMultiLine() const {
    return multiLine_;
}

// ___________________________________________________________________________
int TextField::getFontSize() const {
    return fontSize_;
}

// ___________________________________________________________________________
bool TextField::getBold() const {
    return bold_;
}

// ___________________________________________________________________________
sw::Alignment TextField::getAlignment() const {
    return alignment_;
}


// --- Slider ---

// ___________________________________________________________________________
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
