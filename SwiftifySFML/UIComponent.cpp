//
// Created by Luca Schmitt on 04.08.24.
//

#include <SFML/Graphics.hpp>
#include "UIComponent.h"

#include <string>
#include <iostream>

namespace sw {

    UIComponent::UIComponent(std::string name, sf::Vector2f sizeProportions)
            : name_(std::move(name)), sizeProportions_(sizeProportions) {
        // Assign default values
        needRenderUpdate_ = true;
        isVisible_ = true;

        // Should this be true or false? And should this be renamed to isDisabled?
        isEnabled_ = true;
    }

    // Move constructor
    UIComponent::UIComponent(UIComponent&& other) noexcept
            : needRenderUpdate_(other.needRenderUpdate_),
              isVisible_(other.isVisible_),
              isEnabled_(other.isEnabled_),
              foregroundColor_(std::move(other.foregroundColor_)),
              backgroundColor_(std::move(other.backgroundColor_)),
              name_(std::move(other.name_)),
              parentSize_(other.parentSize_),
              sizeProportions_(other.sizeProportions_),
              position_(other.position_),
              size_(other.size_),
              callback_(std::move(other.callback_)) {
        // Reset the other instance to a valid state
        other.needRenderUpdate_ = false;
        other.isVisible_ = true;
        other.isEnabled_ = true;
        other.parentSize_ = sf::Vector2f(0, 0);
        other.sizeProportions_ = sf::Vector2f(0, 0);
        other.position_ = sf::Vector2f(0, 0);
        other.size_ = sf::Vector2f(0, 0);
    }

    // Move assignment operator
    UIComponent& UIComponent::operator=(UIComponent&& other) noexcept {
        if (this != &other) {
            needRenderUpdate_ = other.needRenderUpdate_;
            isVisible_ = other.isVisible_;
            isEnabled_ = other.isEnabled_;
            foregroundColor_ = std::move(other.foregroundColor_);
            backgroundColor_ = std::move(other.backgroundColor_);
            name_ = std::move(other.name_);
            parentSize_ = other.parentSize_;
            sizeProportions_ = other.sizeProportions_;
            position_ = other.position_;
            size_ = other.size_;
            callback_ = std::move(other.callback_);

            // Reset the other instance to a valid state
            other.needRenderUpdate_ = false;
            other.isVisible_ = true;
            other.isEnabled_ = true;
            other.parentSize_ = sf::Vector2f(0, 0);
            other.sizeProportions_ = sf::Vector2f(0, 0);
            other.position_ = sf::Vector2f(0, 0);
            other.size_ = sf::Vector2f(0, 0);
        }
        return *this;
    }

    void UIComponent::setVisible(bool visible) {
        // Only update visibility and render update flag if needed
        if (isVisible_ != visible) {
            isVisible_ = visible;
            needRenderUpdate_ = true;
        }
    }

    void UIComponent::setEnabled(bool enabled) {
        // Should only the inner line stay here?
        if (isEnabled_ != enabled) {
            isEnabled_ = enabled;
        }
    }

    void UIComponent::setParentSize(sf::Vector2f parentSize) {
        parentSize_ = parentSize;
        computeSize();

        // Update render update flag
        needRenderUpdate_ = true;
    }

    void UIComponent::setSizeProportions(sf::Vector2f sizeProportions) {
        sizeProportions_ = sizeProportions;
        computeSize();

        // Update render update flag
        needRenderUpdate_ = true;
    }

    void UIComponent::setPosition(sf::Vector2f position) {
        position_ = position;

        // Update render update flag
        needRenderUpdate_ = true;
    }

    void UIComponent::updatePosition(sf::Vector2f offset) {
        position_ += offset;

        // Update render update flag
        needRenderUpdate_ = true;
    }

    void UIComponent::setCallback(std::function<void()> callback) {
        callback_ = std::move(callback);
    }

    bool UIComponent::isVisible() const {
        return isVisible_;
    }

    bool UIComponent::isEnabled() const {
        return isEnabled_;
    }

    const std::string &UIComponent::getName() const {
        return name_;
    }

    const sf::Vector2f &UIComponent::getPosition() const {
        return position_;
    }

    const sf::Vector2f &UIComponent::getSize() const {
        return size_;
    }

    void UIComponent::setForegroundColor(sf::Color color) {
        foregroundColor_ = color;
    }

    void UIComponent::setBackgroundColor(sf::Color color) {
        backgroundColor_ = color;
    }

    const sf::Color &UIComponent::getForegroundColor() const {
        return foregroundColor_;
    }

    const sf::Color &UIComponent::getBackgroundColor() const {
        return backgroundColor_;
    }

    bool UIComponent::containsPosition(sf::Vector2f position) const {
        if (position.x > position_.x and position.x < position_.x + size_.x and
            position.y > position_.y and position.y < position_.y + size_.y) {
            return true;
        }

        return false;
    }

    void UIComponent::computeSize() {
        // Compute the actual size. Needs parentSize to be set already.
        size_.x = sizeProportions_.x * parentSize_.x;
        size_.y = sizeProportions_.y * parentSize_.y;

        std::cout << "Did compute size:" << size_.x << ", " << size_.y << std::endl;

//        // Update the parentSize of all child elements
//        for (auto &element: elements_) {
//            std::visit([this](auto &el) { el->setParentSize(size_); }, element);
//        }
    }
}
