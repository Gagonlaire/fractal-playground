#include <utility>
#include "UI.h"

MaterialButton::MaterialButton(sf::Vector2f position, sf::Vector2f size, const std::string &text, sf::Font &font,
                               std::function<void()> onClick) {
    this->onClick = std::move(onClick);
    this->shape.setPosition(position);
    this->shape.setSize(size);
    this->shape.setFillColor(sf::Color(34, 39, 46));
    this->shape.setOutlineColor(sf::Color(69, 76, 86));
    this->text.setString(text);
    this->text.setPosition(position.x + size.x / 2 - this->text.getGlobalBounds().width / 2,
                           position.y + size.y / 2 - this->text.getGlobalBounds().height / 2);
    this->text.setFillColor(sf::Color(69, 76, 86));
    this->text.setFont(font);
    this->shape.setOutlineThickness(2);
}

void MaterialButton::draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}

bool MaterialButton::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                onClick();
                return true;
            }
        }
    }
    return false;
}

void MaterialButton::updateEnabled(bool enabled) {

}
