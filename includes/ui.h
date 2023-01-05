#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct RenderOptions;

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

    ~UiService();

    void draw(sf::RenderWindow &window);

    void dispatchEvent(sf::Event event);
};

class MaterialButton : public UIComponent {
private:
    sf::RectangleShape shape;
    sf::Text _text;
    bool isHovered = false;
    bool isDisabled = false;
    std::function<void()> onClick;

public:
    MaterialButton(
            sf::Vector2f position,
            const std::string &text,
            sf::Font &font,
            std::function<void()> onClick
    );

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(sf::Event event) override;

    void updateEnabled(bool enabled);

    void setPosition(sf::Vector2f);

    sf::Vector2f getPosition();

    void setText(const std::string &text);
};

class MaterialSelector : public UIComponent {
private:
    MaterialButton *selectBox;
    std::vector<std::string> options;
    std::vector<MaterialButton *> options_btn;
    bool isOpen = false;
    std::function<void(int)> onSelect;

public:
    MaterialSelector(
            sf::Vector2f position,
            std::vector<std::string> &options,
            sf::Font &font,
            std::function<void(int)> onSelect
    );

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(sf::Event event) override;
};

class ViewBuilder : public UIComponent {
private:
    bool selecting = false;
    sf::RectangleShape selection;
    std::function<void(sf::Vector2f, sf::Vector2f)> onSelection;

public:
    explicit ViewBuilder(std::function<void(sf::Vector2f, sf::Vector2f)> onSelection);

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(sf::Event event) override;
};
