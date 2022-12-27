#include "UI.h"
#include <iostream>

UiService::UiService() {
    this->font.loadFromFile("resources/Roboto-Regular.ttf");

    // reset view btn
    this->components.push_back(new MaterialButton({15, 15}, "reset view", font, []() {
        std::cout << "Button clicked!" << std::endl;
    }));
    // fractal function selector
    this->components.push_back(new MaterialSelector({200, 15}, {"test", "test2", "test3"}, font, [](int id) {
        std::cout << "Selected: " << id << std::endl;
    }));
    // always add the view builder at the end
    this->components.push_back(new ViewBuilder([](sf::Vector2f pos, sf::Vector2f size) {
        std::cout << "ViewBuilder clicked!" << std::endl;
    }));
}

void UiService::draw(sf::RenderWindow &window) {
    for (auto &component: components) {
        component->draw(window);
    }
}

void UiService::addComponent(UIComponent *component) {
    components.push_back(component);
}

void UiService::removeComponent(UIComponent *component) {
    components.erase(
            std::remove(components.begin(), components.end(), component),
            components.end()
    );
    delete component;
}

void UiService::dispatchEvent(sf::Event event) {
    for (auto &component: components) {
        // if component return true, stop the event propagation
        if (component->handleEvent(event)) {
            break;
        }
    }
}

UiService::~UiService() {
    for (auto &component: components) {
        delete component;
    }
}
