#include "ui.h"

Row::Row(sf::Vector2f position, float spacing, const vector<UIComponent *> &components) {
    _spacing = spacing;
    _components = components;
    _position = position;
    _size = {_spacing, 0};
    _width = _spacing;
    for (auto &component: _components) {
        component->setPosition({position.x + _width, position.y});
        _size.y = std::max(_size.y, component->getSize().y);
        _width += component->getSize().x;
        _width += _spacing;
    }
}

void Row::push_back(UIComponent *component) {
    component->setPosition({_position.x + _width, _position.y});
    _size.y = std::max(_size.y, component->getSize().y);
    _width += component->getSize().x;
    _width += _spacing;
    _components.push_back(component);
}

void Row::push_back(const std::vector<UIComponent *> &components) {
    for (auto &component: components) {
        this->push_back(component);
    }
}

void Row::update() {
    _width = _spacing;
    for (auto &component: _components) {
        component->setPosition({_position.x + _width, _position.y});
        _width += component->getSize().x;
        _width += _spacing;
    }
}

void Row::draw(sf::RenderWindow &window) {
    for (auto &component: _components) {
        component->draw(window);
    }
}

bool Row::handleEvent(sf::RenderWindow &window, sf::Event event) {
    for (auto &component: _components) {
        if (component->handleEvent(window, event)) {
            return true;
        }
    }
    return false;
}

sf::Vector2f Row::getSize() {
    return _size;
}

void Row::setPosition(sf::Vector2f position) {
    // Do nothing
}
