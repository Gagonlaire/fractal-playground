#include <utility>
#include "ui.h"

ViewBuilder::ViewBuilder(std::function<void(sf::Vector2f, sf::Vector2f)> onSelection) {
    this->_onSelection = std::move(onSelection);
    _selection.setFillColor(sf::Color(0, 0, 255, 50));
    _selection.setOutlineThickness(1);
    _selection.setOutlineColor(sf::Color(0, 0, 255, 255));
}

void ViewBuilder::draw(sf::RenderWindow &window) {
    if (_selecting) {
        window.draw(_selection);
    }
}

bool ViewBuilder::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        _selection.setPosition(event.mouseButton.x, event.mouseButton.y);
        _selection.setSize(sf::Vector2f(0, 0));
        _selecting = true;
    } else if (event.type == sf::Event::MouseButtonReleased && _selecting) {
        _selecting = false;
        _onSelection(_selection.getPosition(), _selection.getSize());
        _selection.setSize(sf::Vector2f(0, 0));
        _selection.setPosition(0, 0);
    } else if (event.type == sf::Event::MouseMoved) {
        if (!_selecting) return false;

        _selection.setSize({
                                   event.mouseMove.x - _selection.getPosition().x,
                                   event.mouseMove.y - _selection.getPosition().y
                           });
    }
    return false;
}
