#include "UI.h"
#include <iostream>

MaterialSelector::MaterialSelector(sf::Vector2f position, std::vector<std::string> &options, sf::Font &font,
                                   std::function<void(const std::string &)> onSelect) {
    this->onSelect = std::move(onSelect);
    if (options.empty()) {
        selectBox = new MaterialButton(position, "no options", font, []() {});
        return;
    }
    selectBox = new MaterialButton(position, options[0], font, [this]() {
        isOpen = !isOpen;
    });
    for (int i = 0; i < options.size(); i++) {
        auto *option = new MaterialButton(position + sf::Vector2f(0, 60.0 * (i + 1)), options[i], font,
                                          [this, i, options]() {
                                              selectBox->setText(options[i]);
                                              isOpen = false;
                                              this->onSelect(options[i]);
                                          });
        this->options.push_back(option);
    }
}

void MaterialSelector::draw(sf::RenderWindow &window) {
    selectBox->draw(window);
    if (isOpen) {
        for (auto option: options) {
            option->draw(window);
        }
    }
}

bool MaterialSelector::handleEvent(sf::Event event) {
    if (isOpen) {
        for (auto option: options) {
            if (option->handleEvent(event)) {
                return true;
            }
        }
    }
    return selectBox->handleEvent(event);
}
