//
// Created by Luca Schmitt on 26.07.24.
//

#ifndef SWIFTIFYSFML_V0_1_UICOMPONENT_H
#define SWIFTIFYSFML_V0_1_UICOMPONENT_H

namespace sw {

    class UIComponent {
    public:
        // Constructor and destructor
        UIComponent(std::string name, sf::Vector2f sizeProportions);
        virtual ~UIComponent() = default;

        // Delete copy constructor and copy assignment operator
        UIComponent(const UIComponent&) = delete;
        UIComponent& operator=(const UIComponent&) = delete;

        // Move constructor
        UIComponent(UIComponent&& other) noexcept;

        // Move assignment operator
        UIComponent& operator=(UIComponent&& other) noexcept;

        // Setter functions

        // Accessibility
        void setVisible(bool visible);
        void setEnabled(bool enabled);

        void setForegroundColor(sf::Color color);
        void setBackgroundColor(sf::Color color);

        void setCallback(std::function<void()> callback);

        // Layout-related properties
        void setParentSize(sf::Vector2f parentSize);

        void setSizeProportions(sf::Vector2f sizeProportions);

        void setPosition(sf::Vector2f position);

        void updatePosition(sf::Vector2f offset);

        // Getter functions

        // Get visibility and responsiveness flags
        [[nodiscard]] bool isVisible() const;
        [[nodiscard]] bool isEnabled() const;

        // Get internal properties, only as const references
        [[nodiscard]] const std::string &getName() const;
        [[nodiscard]] const sf::Vector2f &getPosition() const;
        [[nodiscard]] virtual const sf::Vector2f &getSize() const;
        [[nodiscard]] const sf::Color &getForegroundColor() const;
        [[nodiscard]] const sf::Color &getBackgroundColor() const;

        // Check if a given position in within the UIComponent's bounds
        bool containsPosition(sf::Vector2f position) const;

        // UI-related functions

        // Draws the UI component to the screen according to the render information
        virtual void draw(sf::RenderWindow &window) = 0;

        // Handle events such as mouse clicks or key presses
        virtual bool handleEvent(const sf::Event &event) = 0;

        // Update the render information for the UI component
        virtual void computeRenderInformation() = 0;

    protected:
        // Computet the size from the parentSize and sizeProportions
        virtual void computeSize();

        // Flag indicating if the render information needs to be updated. Only set internally.
        bool needRenderUpdate_;

        // Flags indicating visibility and responsiveness
        bool isVisible_;
        bool isEnabled_;

        // Colors for front and background
        sf::Color foregroundColor_;
        sf::Color backgroundColor_;

        // Name for identification. Probably only used in events and interactions. Set in the constructor and can only be
        // gotten afterward.
        std::string name_;

        // Absolute size of the parent container. Calculated internally
        sf::Vector2f parentSize_;

        // Size proportion of the UIComponent in relation to the parent container. Can be set via setter functions.
        sf::Vector2f sizeProportions_;

        // Position can be set by the parent container and be gotten as a const reference
        sf::Vector2f position_;

        // Computed from the proportions. Therefore, these can only be
        // gotten and not set.
        sf::Vector2f size_;

        // Stores the callback function that should be executed when an event is recognized.
        std::function<void()> callback_;
    };

}

#endif //SWIFTIFYSFML_V0_1_UICOMPONENT_H
