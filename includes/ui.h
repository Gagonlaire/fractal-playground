#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using std::string, std::vector;

struct RenderOptions;

class UIComponent {
public:
    virtual void draw(sf::RenderWindow &) = 0;

    virtual bool handleEvent(sf::RenderWindow &, sf::Event) = 0;

    virtual sf::Vector2f getSize() = 0;

    virtual void setPosition(sf::Vector2f) = 0;

    virtual ~UIComponent() = default;
};

class UiService {
private:
    std::vector<UIComponent *> _components;
    sf::Font _font;

public:
    UiService();

    ~UiService();

    void draw(sf::RenderWindow &);

    void dispatchEvent(sf::RenderWindow &, sf::Event);
};

class Row : public UIComponent {
private:
    std::vector<UIComponent *> _components;
    sf::Vector2f _size;
    sf::Vector2f _position;
    float _spacing;
    float _width;

public:
    Row(sf::Vector2f, float, const vector<UIComponent *> &);

    void draw(sf::RenderWindow &) override;

    bool handleEvent(sf::RenderWindow &, sf::Event) override;

    sf::Vector2f getSize() override;

    void setPosition(sf::Vector2f) override;

    void update();

    void push_back(UIComponent *);

    void push_back(const std::vector<UIComponent *> &);
};

class MaterialBox : public UIComponent {
private:
    sf::RectangleShape _shape;
    sf::Text _text;

public:
    MaterialBox(sf::Vector2f, sf::Vector2f, sf::Font &, const string &);

    void draw(sf::RenderWindow &) override;

    bool handleEvent(sf::RenderWindow &, sf::Event) override;

    sf::Vector2f getSize() override;

    void setPosition(sf::Vector2f position) override;

    void setText(const string &text);
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

    bool handleEvent(sf::RenderWindow &, sf::Event event) override;

    sf::Vector2f getSize() override;

    void setPosition(sf::Vector2f) override;

    void updateEnabled(bool enabled);

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

    bool handleEvent(sf::RenderWindow &, sf::Event event) override;

    sf::Vector2f getSize() override;

    void setPosition(sf::Vector2f) override;
};

class ViewBuilder : public UIComponent {
private:
    bool _selecting = false;
    sf::RectangleShape _selection;
    std::function<void(sf::Vector2f, sf::Vector2f)> _onSelection;

public:
    explicit ViewBuilder(std::function<void(sf::Vector2f, sf::Vector2f)> onSelection);

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(sf::RenderWindow &, sf::Event event) override;

    sf::Vector2f getSize() override;

    void setPosition(sf::Vector2f) override;
};
