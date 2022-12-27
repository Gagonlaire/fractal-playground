#include <utility>
#include "UI.h"

MaterialButton::MaterialButton(sf::Vector2f position, const std::string &text, sf::Font &font,
                               std::function<void()> onClick) {
    this->onClick = std::move(onClick);
    this->shape.setPosition(position);
    this->shape.setFillColor(DARK);
    this->shape.setOutlineColor(WHITE);
    this->_text.setString(text);
    this->_text.setFillColor(WHITE);
    this->_text.setFont(font);
    this->shape.setSize({this->_text.getGlobalBounds().width + 25, 50});
    this->_text.setPosition(position + sf::Vector2f(11, 5));
    this->shape.setOutlineThickness(2);
}

void MaterialButton::draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(_text);
}

bool MaterialButton::handleEvent(sf::Event event) {
    if (this->isDisabled) {return false;}

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                onClick();
                return true;
            }
        }
    } else if (event.type == sf::Event::MouseMoved) {
        if (shape.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
            shape.setFillColor(WHITE);
            _text.setFillColor(DARK);
            shape.setOutlineColor(DARK);
        } else {
            shape.setFillColor(DARK);
            _text.setFillColor(WHITE);
            shape.setOutlineColor(WHITE);
        }
    }
    return false;
}

void MaterialButton::updateEnabled(bool enabled) {
    this->isDisabled = !enabled;
    sf::Color textColor = _text.getFillColor();
    sf::Color shapeColor = shape.getFillColor();
    sf::Color outlineColor = shape.getOutlineColor();

    if (enabled) {
        textColor.a = 255;
        shapeColor.a = 255;
        outlineColor.a = 255;
    } else {
        textColor.a = 100;
        shapeColor.a = 100;
        outlineColor.a = 100;
    }
    _text.setFillColor(textColor);
    shape.setFillColor(shapeColor);
    shape.setOutlineColor(outlineColor);
}

void MaterialButton::setText(const std::string &text) {
    this->_text.setString(text);
    this->shape.setSize({this->_text.getGlobalBounds().width + 25, this->_text.getGlobalBounds().height + 30});
    this->_text.setPosition(shape.getPosition() + sf::Vector2f(11, 5));
}
