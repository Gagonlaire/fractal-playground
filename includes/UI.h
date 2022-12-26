#pragma once

#include <SFML/Graphics.hpp>

// create a interface for UI components
class UIComponent {
public:
    virtual void draw(sf::RenderWindow &window) = 0;

    virtual bool handleEvent(sf::Event event) = 0;

    virtual ~UIComponent() = default;
};

class UiService {
private:
    std::vector<UIComponent *> components;
    sf::Font font;

public:
    UiService();

    void draw(sf::RenderWindow &window);

    void addComponent(UIComponent *component);

    void removeComponent(UIComponent *component);

    void dispatchEvent(sf::Event event);
};

class MaterialButton : public UIComponent {
private:
    sf::RectangleShape shape;
    sf::Text text;
    bool isHovered = false;
    bool isDisabled = false;
    std::function<void()> onClick;

public:
    MaterialButton(
            sf::Vector2f position,
            sf::Vector2f size,
            const std::string &text,
            sf::Font &font, std::function<void()> onClick
    );

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(sf::Event event) override;

    void updateEnabled(bool enabled);
};
