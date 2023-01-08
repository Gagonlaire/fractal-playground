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
    std::vector<UIComponent *> _components;
    sf::Font _font;

public:
    UiService();

    ~UiService();

    void draw(sf::RenderWindow &window);

    void dispatchEvent(sf::Event event);
};

class MaterialButton : public UIComponent {
private:
    sf::RectangleShape _shape;
    sf::Text _text;
    bool _isHovered = false;
    bool _isDisabled = false;
    std::function<void()> _onClick;

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
    MaterialButton *_selectBox;
    std::vector<std::string> _options;
    std::vector<MaterialButton *> _options_btn;
    bool _isOpen = false;
    std::function<void(int)> _onSelect;

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
    bool _selecting = false;
    sf::RectangleShape _selection;
    std::function<void(sf::Vector2f, sf::Vector2f)> _onSelection;

public:
    explicit ViewBuilder(std::function<void(sf::Vector2f, sf::Vector2f)> onSelection);

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(sf::Event event) override;
};
