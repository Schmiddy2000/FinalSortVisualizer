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
public:
    // Constructor and destructor
    Text(std::string name, sf::Vector2f sizeProportions, std::string content);
    // ~Text() = default;

    // Modify the text appearance
    void setFontSize(int fontSize);
    void setBold(bool bold);
    void setContent(const std::string &content);

    // Uses window.draw to render the text to the screen
    void draw(sf::RenderWindow& window) override;

    // Handle events.
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

    // Setter for text field modifications
    void setMultiLine(bool multiLine);
    void setFontSize(int fontSize);
    void setBold(bool bold);
    void setAlignment(sw::Alignment alignment);

    // Getters for text field modifications
    bool getMultiLine() const;
    int getFontSize() const;
    bool getBold() const;
    sw::Alignment getAlignment() const;

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
    std::vector<Text> textLines_;
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


/*
 * DatasetVisualizer class. Visualizes the normalized data from a Dataset instance using bars of
 * variable height. Should feature some subsection selection mechanism (only used in the generation process).
 *
 * Ideas for subsection selection mechanisms:
 * 1) Use the normalized data bars
 * 2) Display an additional set of bars (same height, 5-10 % of the UI element) with the sole purpose
 * of handling the input. Maybe this could also be a horizontal bar if clicks aren't always recognized
 * (for many bars, due to the gaps between them...)
 * --> These could either work with click or drag input (or both...)
 *
 * --- Updated after writing SwiftifySFML ---
 * Thoughts on the layout:
 * - Place all components inside a container
 *
 * Thoughts on the data / attributes needed:
 * -
 *
 * Thought on the interactions:
 * -
 *
 * Additional thoughts:
 * - Use this in combination with another visualizer that handles the subsection selection when creating datasets
 * and don't add the additional functionality for that here.
 * - Can this simply use a pointer to the normalized data in the Dataset class instance? Or should the
 * SortingVisualizer contain all the information? Or can it even just be gotten from the Dataset class instance,
 * maybe by setting the data public?
 */
class DatasetVisualizer: public sw::UIComponent {
public:
    // Constructor. Should have a bool subsectionSelection determining if this feature should be displayed / enabled.
    DatasetVisualizer(std::string name, sf::Vector2f sizeProportions);
    ~DatasetVisualizer() = default;

    // ...
    void draw(sf::RenderWindow& window) override;
    bool handleEvent(const sf::Event& event) override;
    void computeRenderInformation() override;

private:
    // Should either have a ref / pointer to the dataset instance and set the subsection indices itself, or the
    // sort / shuffle functions should be extended to take indices as parameters and then be called...
    // Since we need to manage first clicks where we can't know if it is the start or stop index, having these
    // parameters here might be better...
    // --> Have to update the parameters (and inner workings) of the sort and shuffle functions
    size_t subsectionStart_;
    size_t subsectionStop_;

    // Technically, we only need (a pointer to) the normalized data (plus maybe the section indices). But my gut
    // tells me that we'll probably need more information at some point, so having access to a sorter instance
    // (that will contain a dataset instance) is a better choice...
    // Then we would have to use a templated variable though. For that, I would have to use std::variant. If I use
    // variant, can or do I have to use unique pointers then? Because this might be a problem due to unique
    // ownership...
    // ...
};


/*
 * StatisticsVisualizer class. Shows the result of the tracking components of the sorter class. Might also have
 * buttons and sliders to set up the benchmark parameters to run benchmark tests there (would then also show the
 * benchmark results there...)
 *
 * --- Updated after writing SwiftifySFML ---
 * Thoughts on the layout:
 * - Place all components inside a container
 *
 * Thoughts on the data / attributes needed:
 * -
 *
 * Thought on the interactions:
 * -
 */
class StatisticsVisualizer: public sw::UIComponent {
public:
    // Constructor and destructor

    // Definition of purely virtual functions
    void draw(sf::RenderWindow& window) override;
    bool handleEvent(const sf::Event& event) override;
    void computeRenderInformation() override;

private:
    // Variables and potentially internal functions
};


/*
 * PlotVisualizer class. Shows the history of the tracking components of the sorter class (component-wise) as
 * a (line?) plot (probably scatter but after a few steps should look like a line). This will very likely just
 * plot the accumulated values of the tracking components against the sorting steps. Maybe we will also add a
 * plot that shows the values for each step, but this will break once we have more steps than pixels in the
 * UI element (width-wise)...
 */
class PlotVisualizer: public sw::UIComponent {
public:
    // Constructor and destructor

    // Definition of purely virtual functions
    void draw(sf::RenderWindow& window) override;
    bool handleEvent(const sf::Event& event) override;
    void computeRenderInformation() override;

private:
    // Variables and potentially internal functions
};


/*
 * SortingVisualizer.
 *
 * Maybe we would like to create a sortingVisualizer that has a DatasetVisualizer, a StatisticsVisualizer and
 * a PlotVisualizer. This component could then kind of function as a small screen. Here we could then have 3 buttons
 * at the top of the UI element that lets the user choose which type of information (visualizer) he would like to have
 * displayed right now...
 * (Additionally, we could also add a TextField (or event dedicated informationVisualizer) that would tell the user
 * something about the specific sorting algorithm)
 *
 * This component could also handle the event handling and logic (what to currently display) on its own, increasing
 * modularity. Else, this has to be done by the screen class instance...
 *
 * --> Then we would also only need one sorter and dataset instance for all three UI elements and would not need to
 * copy / move these instances.
 *
 * --- Updated after writing SwiftifySFML ---
 * Thoughts on the layout:
 * - Place all components inside a container
 *
 * Thoughts on the data / attributes needed:
 * -
 *
 * Thought on the interactions:
 * -
 */
class SortingVisualizer: public sw::UIComponent {
public:
    // Constructor.

    // Functions to switch to the different components (will probably update the corresponding render information
    // (if needed)). They will also probably update the value of a variable storing the case of the current screen
    // in an enum. Then I can use a switch to show the requested content.

    // Render function should contain the switch (and then call the render function of the wanted class instance)

    // Update render information should call the selected class instances update render information function

    // Handle event function should handle different information component selection or pass down the event
    // information (is there a case for this ???)

private:
    // Local enum (maybe placeholder but maybe enough...) + maybe add 'Information'
    enum class ActiveVisualizer { Dataset, Statistics, Plot };
    // Variable to store the Visualizer to currently display
    ActiveVisualizer activeVisualizer_;

    // Visualizer instances (will they be passed or created here? --> Probably here)
    // Currently commented out since the classes still have undefined virtual functions
//    DatasetVisualizer datasetVisualizer_;
//    StatisticsVisualizer statisticsVisualizer_;
//    PlotVisualizer plotVisualizer_;

    // Sorter instance pointer
    // Sorter* sorter_
};

#endif //FINALSORTVISUALIZER_UICOMPONENTS_H
