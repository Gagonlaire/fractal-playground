#include "ui.h"
#include <iostream>

float SELECTOR_OFFSET = 60;

MaterialSelector::MaterialSelector(sf::Vector2f position, std::vector<std::string> &options, sf::Font &font,
                                   std::function<void(int)> onSelect) {
    this->_onSelect = std::move(onSelect);

    if (options.empty()) {
        options.emplace_back("no options");
    }
    _selectBox = new MaterialButton(position, options[0], font, [this]() {
        _isOpen = !_isOpen;
    });
    for (int i = 0; i < options.size(); i++) {
        auto *option = new MaterialButton(position + sf::Vector2f(0, SELECTOR_OFFSET * (i + 1)), options[i], font,
                                          [this, i, options]() {
                                              _selectBox->setText(options[i]);
                                              _isOpen = false;
                                              this->_onSelect(i);
                                          });
        this->_options_btn.push_back(option);
    }
}

void MaterialSelector::draw(sf::RenderWindow &window) {
    _selectBox->draw(window);
    if (_isOpen) {
        for (auto btn: _options_btn) {
            btn->draw(window);
        }
    }
}

bool MaterialSelector::handleEvent(sf::Event event) {
    if (_isOpen) {
        for (auto btn: _options_btn) {
            if (btn->handleEvent(event)) {
                return true;
            }
        }
    }
    return _selectBox->handleEvent(event);
}
