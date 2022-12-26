#include "UI.h"
#include <iostream>

UiService::UiService() {
    this->font.loadFromFile("resources/Roboto-Regular.ttf");

    // reset view btn
    this->components.push_back(new MaterialButton({0, 0}, {100, 50}, "Click me", font, []() {
        std::cout << "Button clicked!" << std::endl;
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
