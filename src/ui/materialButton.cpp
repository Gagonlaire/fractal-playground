#include <utility>
#include "ui.h"

MaterialButton::MaterialButton(sf::Vector2f position, const std::string &text, sf::Font &font,
                               std::function<void()> onClick) {
    this->_onClick = std::move(onClick);
    this->_shape.setPosition(position);
    this->_shape.setFillColor(sf::Color::Black);
    this->_shape.setOutlineColor(sf::Color::White);
    this->_text.setString(text);
    this->_text.setFillColor(sf::Color::White);
    this->_text.setFont(font);
    this->_shape.setSize({this->_text.getGlobalBounds().width + 25, 50});
    this->_text.setPosition(position + sf::Vector2f(11, 5));
    this->_shape.setOutlineThickness(2);
}

void MaterialButton::draw(sf::RenderWindow &window) {
    window.draw(_shape);
    window.draw(_text);
}

bool MaterialButton::handleEvent(sf::RenderWindow &window, sf::Event event) {
    if (this->_isDisabled) {return false;}

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (_shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                _onClick();
                return true;
            }
        }
    } else if (event.type == sf::Event::MouseMoved) {
        bool contains = _shape.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y);

        if (contains && !_isHovered) {
            _isHovered = true;
            _shape.setFillColor(sf::Color::White);
            _text.setFillColor(sf::Color::Black);
            _shape.setOutlineColor(sf::Color::Black );

            sf::Cursor cursor;
            cursor.loadFromSystem(sf::Cursor::Hand);
            window.setMouseCursor(cursor);
        }
        if (!contains && _isHovered) {
            _isHovered = false;
            _shape.setFillColor(sf::Color::Black);
            _text.setFillColor(sf::Color::White);
            _shape.setOutlineColor(sf::Color::White);

            sf::Cursor cursor;
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window.setMouseCursor(cursor);
        }
    }
    return false;
}

void MaterialButton::updateEnabled(bool enabled) {
    this->_isDisabled = !enabled;
    sf::Color textColor = _text.getFillColor();
    sf::Color shapeColor = _shape.getFillColor();
    sf::Color outlineColor = _shape.getOutlineColor();

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
    _shape.setFillColor(shapeColor);
    _shape.setOutlineColor(outlineColor);
}

void MaterialButton::setText(const std::string &text) {
    this->_text.setString(text);
    this->_shape.setSize({this->_text.getGlobalBounds().width + 25, 50});
    this->_text.setPosition(_shape.getPosition() + sf::Vector2f(11, 5));
}

void MaterialButton::setPosition(sf::Vector2f position) {
    this->_shape.setPosition(position);
    this->_text.setPosition(position + sf::Vector2f(11, 5));
}

sf::Vector2f MaterialButton::getSize() {
    return this->_shape.getSize();
}
