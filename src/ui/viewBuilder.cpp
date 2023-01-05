#include <utility>
#include "ui.h"

ViewBuilder::ViewBuilder(std::function<void(sf::Vector2f, sf::Vector2f)> onSelection) {
    this->onSelection = std::move(onSelection);
    selection.setFillColor(sf::Color(0, 0, 255, 50));
    selection.setOutlineThickness(1);
    selection.setOutlineColor(sf::Color(0, 0, 255, 255));
}

void ViewBuilder::draw(sf::RenderWindow &window) {
    if (selecting) {
        window.draw(selection);
    }
}

bool ViewBuilder::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            selection.setPosition(event.mouseButton.x, event.mouseButton.y);
            selection.setSize(sf::Vector2f(0, 0));
            selecting = true;
        }
    } else if (event.type == sf::Event::MouseButtonReleased && selecting) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            selecting = false;
            onSelection(selection.getPosition(), selection.getSize());
            selection.setSize(sf::Vector2f(0, 0));
            selection.setPosition(0, 0);
        }
    } else if (event.type == sf::Event::MouseMoved) {
        if (!selecting) return false;

        selection.setSize({
            event.mouseMove.x - selection.getPosition().x,
            event.mouseMove.y - selection.getPosition().y
        });
    }
    return false;
}
