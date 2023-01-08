#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using std::string, std::vector;

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

class MaterialBox : public UIComponent {
private:
    sf::RectangleShape _shape;
    sf::Text _text;

public:
    MaterialBox(sf::Vector2f position, sf::Vector2f size, sf::Font &font, const string &text);

    void draw(sf::RenderWindow &window) override;

    void setText(const string &text);

    bool handleEvent(sf::Event event) override;
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
            const string &text,
            sf::Font &font,
            std::function<void()> onClick
    );

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(sf::Event event) override;

    void updateEnabled(bool enabled);

    void setPosition(sf::Vector2f);

    sf::Vector2f getPosition();

    void setText(const string &text);
};

class MaterialSelector : public UIComponent {
private:
    MaterialButton *_selectBox;
    std::vector<string> _options;
    std::vector<MaterialButton *> _options_btn;
    bool _isOpen = false;
    std::function<void(int)> _onSelect;

public:
    MaterialSelector(
            sf::Vector2f position,
            vector<string> &options,
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
