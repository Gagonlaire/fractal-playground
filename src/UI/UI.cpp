#include "UI.h"
#include "fractal-playground.h"
#include <iostream>

UiService::UiService() {
    this->font.loadFromFile("resources/Roboto-Regular.ttf");

    // reset view btn
    this->components.push_back(new MaterialButton({15, 15}, "reset view", font, []() {
        std::cout << "Button clicked!" << std::endl;
    }));
    // build options from fractalFunctions map
    std::vector<std::string> _options;
    for (auto &item: fractalFunctions) {
        _options.push_back(item.first);
    }
    // fractal function selector
    this->components.push_back(new MaterialSelector({200, 15}, _options, font, [](const std::string &option) {
        options.function = fractalFunctions.at(option);
        computeTexture();
    }));
    // always add the view builder at the end
    this->components.push_back(new ViewBuilder([](sf::Vector2f pos, sf::Vector2f size) {
        options.minRe = options.minRe + (options.maxRe - options.minRe) * pos.x / (options.size.x - 1);
        options.maxRe = options.minRe + (options.maxRe - options.minRe) * (pos.x + size.x) / (options.size.x - 1);
        options.minIm = options.minRe / options.aspectRatio;
        options.maxIm = options.maxRe / options.aspectRatio;
        computeTexture();
    }));
}

void UiService::draw(sf::RenderWindow &window) {
    for (auto &component: components) {
        component->draw(window);
    }
}

void UiService::dispatchEvent(sf::Event event) {
    for (auto &component: components) {
        // if component return true, stop the event propagation
        if (component->handleEvent(event)) {
            std::cout << "Event handled by component" << std::endl;
            break;
        }
    }
}

UiService::~UiService() {
    for (auto &component: components) {
        delete component;
    }
}
