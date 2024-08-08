//
// Created by Luca Schmitt on 07.08.24.
//

#ifndef FINALSORTVISUALIZER_UICOMPONENTS_H
#define FINALSORTVISUALIZER_UICOMPONENTS_H

#include <SFML/Graphics.hpp>
#include "../SwiftifySFML/Container.h"
#include "../SwiftifySFML/UIComponent.h"
#include "../SwiftifySFML/Enumerations.h"


/*
 * Button class. Can be interacted with by mouse clicks.
 *
 * Additional parameters:
 * - label
 * Should this have a default for fontSize and textAlignment, or should it be specifiable? And if so, where?
 */
class Button: public sw::UIComponent {
public:
    // Constructor with base construction and adding the label. Here we move the string to avoid unnecessary copying
    Button(std::string name, sf::Vector2f sizeProportions, std::string label);

    // Override the render method here. This should only draw to the screen
    void draw(sf::RenderWindow& window) override;

    // Here we still have to think about the return to signalize the higher-level view component that an action
    // has to be performed...
    bool handleEvent(const sf::Event& event) override;

    // Write a get render instructions function here that computes the information needed to render the button in the
    // initializer and when any relevant parameters change. This should reduce the computational cost since the render
    // function will be called every frame
    void computeRenderInformation() override;

private:
    // Render update flag
    bool needRenderUpdate_;

    // Store the label string
    std::string label_;

    // Add parameters to store the precomputed sf::RectangleShape and a sf::Text instances here
    sf::RectangleShape buttonShape_;
    sf::Text buttonLabel_;
};


/*
 * Basic implementation that can display a one-lined string.
 * Essentially the same as sf::Text but as a UIComponent
 * and more basic.
 */
class Text: public sw::UIComponent {
    // Constructor and destructor
    Text(std::string name, sf::Vector2f sizeProportions, std::string content);
    ~Text() = default;

    // Modify the text appearance
    void setFontSize(int fontSize);
    void setBold(bool bold);
    void setContent(const std::string &content);

    // Loops over all text lines and uses window.draw to render them to the screen
    void draw(sf::RenderWindow& window) override;

    // TextFields should probably not have to handle events.
    bool handleEvent(const sf::Event& event) override;

    // Compute the render information for the sf::Text
    void computeRenderInformation() override;

private:
    // Render update flag
    bool needRenderUpdate_;

    // Appearance modifications
    int fontSize_;
    bool bold_;

    // Store the content
    std::string content_;

    // Store the render information
    sf::Text text_;
};


/*
 * TextField class. Can display a string on screen. Should also have the boolean parameter multiLine. It Can probably
 * also be used as a spacer.
 *
 * Does this need a size parameter? It Can probably be used as a max size and then decrease the font size if the text
 * is too large for the specified size.
 *
 * Additional parameters:
 * - bool multiLine
 * - int / float fontSize
 * - Alignment textAlignment
 * - content
 * - Can the TextField class use the background parameter?
 *
 * Thoughts on the constructor and general structure:
 * - Maybe set fontSize, alignment, and multiline to default values when initializing. In this case TextField needs
 * setter functions for these parameters.
 *
 * Additional thoughts:
 * - Currently, contentToTextLines already does what getRenderInstructions is supposed to do.
 * - Clang-Tidy complains about 'recursive call chain' inside contentToTextLines, since this function can call
 * itself recursively.
 * --> contentToTextLines should calculate the render instructions for the current font size and
 * getRenderInstructions should handle the recursive logic. This would make the code more modular and
 * easier to maintain.
 *
 *
 * --- This class could probably be rather easily improved using Containers ---
 *
 */
class TextField: public sw::UIComponent {
public:
    // Constructor
    // Is the passing of content, fontsize, alignment, and multiLine needed? Or should it take default values and
    // use setter functions?
    TextField(std::string name, sf::Vector2f sizeProportions, std::string content);

      //, int fontSize, bool bold, sw::Alignment alignment, bool multiLine); → Set with setters

    // Turns the content into textLines that fit into the maximum size. Should be called in the init. TextLines only
    // contain string information at this point. Also updates the fontSize if needed.
    //
    // Rework: creates the textLines for the current fontSize. Returns false, if size.y is too small to fit
    // all textLines. Else it returns true. Can be called recursively in getRenderInstructions(), reducing fontSize
    // each time.
    // --> Or it could return the line height and then smarter things that fontSize -= 1 can be done.
    float contentToTextLines();

    // Returns the minimal size of the textField itself. Calculated by taking the maximum text box width and
    // summing over all text box heights.
    sf::Vector2f getRealSize();

    // Modifies the positions of the instances in textLines_ to get a coherent text block with the specified
    // alignment. Also sets the other sf::Text attributes.
    void computeRenderInformation() override;

    // Loops over all text lines and uses window.draw to render them to the screen
    void draw(sf::RenderWindow& window) override;

    // TextFields should probably not have to handle events.
    bool handleEvent(const sf::Event& event) override;

    // Probably won't have any subclass-specific setter or getter functions except getRealSize()

private:
    // Function to split a string by space characters to get a vector with words
    std::vector<std::string> splitString(const std::string &str, char delimiter);

    // Render update flag
    bool needRenderUpdate_;

    // Modification parameters
    bool multiLine_;
    int fontSize_;
    bool bold_;
    sw::Alignment alignment_;

    // Storing the - possibly multiple - lines of text
    std::vector<sf::Text> textLines_;
    std::string content_;

    // Container to store and align the text lines
    sw::Container container_;
};


/*
 * Slider class. Can be interacted with by mouse drags (and clicks?). Displays a sliderBar with an overlayed
 * sliderKnob. Also displays min, max and current value.
 *
 *                     currentValue
 * Appearance: minValue <===0===> maxValue
 */
class Slider: public sw::UIComponent {
public:
    // Constructor
    Slider(std::string name, const sf::Vector2f sizeProportions, int minValue, int maxValue);
    ~Slider() = default;

    // The min and max values will be passed to the slider for initiation. Therefore, we will very likely won't need
    // getters for those. They will be used in the handleEvent function internally since this determines the
    // slider reactance to sliderKnob movement. According to this movement, we'll need to update (and rerender) the
    // current value (text).
    // -->
    void draw(sf::RenderWindow& window) override;
    bool handleEvent(const sf::Event& event) override;
    void computeRenderInformation() override;

    // Additionally, we want to create a function that (only partially) updates the UI subcomponents (only for the
    // ones that will be changed, i.e., sliderKnob and currentValue). Should be called in the handleEvent function.
    void updateRenderInstructions();

private:
    // Render update flag
    bool needRenderUpdate_;

    // Think about the types (not that important though). Either do static_casts or template this. No templating
    // needed, since diversity and size are ints, right?
    int minValue_;















    int maxValue_;
    int currentValue_;

    // UI Subcomponents
    sf::RectangleShape sliderBar_;
    sf::CircleShape sliderKnob_;

    // TextFields for the values (Do these need a background...?)
    // The font size should be fixed (or proportionally dynamic if we implement a dynamic layout helper)
    sf::Text minValueText_;
    sf::Text maxValueText_;
    sf::Text currentValueText_;
};

#endif //FINALSORTVISUALIZER_UICOMPONENTS_H
