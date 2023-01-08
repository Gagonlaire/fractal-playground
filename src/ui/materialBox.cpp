#include "ui.h"

MaterialBox::MaterialBox(sf::Vector2f position, sf::Vector2f size, sf::Font &font, const string &text) {
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

void MaterialBox::draw(sf::RenderWindow &window) {
    window.draw(this->_shape);
    window.draw(this->_text);
}

bool MaterialBox::handleEvent(sf::RenderWindow &, sf::Event event) {
    return false;
}

void MaterialBox::setText(const string &text) {
    this->_text.setString(text);
    this->_shape.setSize({this->_text.getGlobalBounds().width + 25, 50});
}

sf::Vector2f MaterialBox::getSize() {
    return this->_shape.getSize();
}

void MaterialBox::setPosition(sf::Vector2f position) {
    this->_shape.setPosition(position);
    this->_text.setPosition(position + sf::Vector2f(11, 5));
}
