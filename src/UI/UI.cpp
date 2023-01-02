#include "UI.h"
#include "fractal-playground.h"
#include "data.h"
#include <iostream>

UiService::UiService() {
    this->font.loadFromFile("resources/Roboto-Regular.ttf");

    // reset view btn
    this->components.push_back(new MaterialButton({15, 15}, "reset view", font, []() {
        options.minRe = std::get<0>(options.function.defaultView);
        options.maxRe = std::get<1>(options.function.defaultView);
        options.minIm = std::get<2>(options.function.defaultView);
        options.maxIm = std::get<3>(options.function.defaultView);

        computeTexture();
        history.clear();
    }));
    // view history btn
    this->components.push_back(new MaterialButton({200, 15}, "go back", font, []() {
        if (!history.empty()) {
            auto value = history.back();
            history.pop_back();
            options.minRe = std::get<0>(value);
            options.maxRe = std::get<1>(value);
            options.minIm = std::get<2>(value);
            options.maxIm = std::get<3>(value);
            computeTexture();
        }
    }));
    // build options from fractalFunctions map
    std::vector<std::string> _options;
    for (auto &item: fractalFunctions) {
        _options.push_back(item.name);
    }
    // fractal function selector
    this->components.push_back(new MaterialSelector({357, 15}, _options, font, [](int index) {
        options.function = fractalFunctions[index];
        options.minRe = std::get<0>(options.function.defaultView);
        options.maxRe = std::get<1>(options.function.defaultView);
        options.minIm = std::get<2>(options.function.defaultView);
        options.maxIm = std::get<3>(options.function.defaultView);
        computeTexture();
    }));
    // always add the view builder at the end
    this->components.push_back(new ViewBuilder([](sf::Vector2f pos, sf::Vector2f size) {
        if (size.x < 10 || size.y < 10) return;

        history.emplace_back(options.minRe, options.maxRe, options.minIm, options.maxIm);
        options.minRe = options.minRe + (options.maxRe - options.minRe) * pos.x / (options.size.x - 1);
        options.maxRe = options.minRe + (options.maxRe - options.minRe) * (pos.x + size.x) / (options.size.x - 1);
        options.minIm = options.minIm + (options.maxIm - options.minIm) * pos.y / (options.size.y - 1);
        options.maxIm = options.minIm + (options.maxIm - options.minIm) * (pos.y + size.y) / (options.size.y - 1);
        double aspectRatio = (double) options.size.x / options.size.y;
        long double newWidth = (options.maxIm - options.minIm) * aspectRatio;
        long double diff = newWidth - (options.maxRe - options.minRe);

        options.minRe -= diff / 2;
        options.maxRe += diff / 2;
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
            break;
        }
    }
}

UiService::~UiService() {
    for (auto &component: components) {
        delete component;
    }
}
