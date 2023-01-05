#include "ui.h"
#include <iostream>

float SELECTOR_OFFSET = 60;

MaterialSelector::MaterialSelector(sf::Vector2f position, std::vector<std::string> &options, sf::Font &font,
                                   std::function<void(int)> onSelect) {
    this->onSelect = std::move(onSelect);

    if (options.empty()) {
        options.emplace_back("no options");
    }
    selectBox = new MaterialButton(position, options[0], font, [this]() {
        isOpen = !isOpen;
    });
    for (int i = 0; i < options.size(); i++) {
        auto *option = new MaterialButton(position + sf::Vector2f(0, SELECTOR_OFFSET * (i + 1)), options[i], font,
                                          [this, i, options]() {
                                              selectBox->setText(options[i]);
                                              isOpen = false;
                                              this->onSelect(i);
                                          });
        this->options_btn.push_back(option);
    }
}

void MaterialSelector::draw(sf::RenderWindow &window) {
    selectBox->draw(window);
    if (isOpen) {
        for (auto btn: options_btn) {
            btn->draw(window);
        }
    }
}

bool MaterialSelector::handleEvent(sf::Event event) {
    if (isOpen) {
        for (auto btn: options_btn) {
            if (btn->handleEvent(event)) {
                return true;
            }
        }
    }
    return selectBox->handleEvent(event);
}
