#include "ui.h"
#include "data.h"

UiService::UiService() {
    this->_font.loadFromFile("resources/Roboto-Regular.ttf");

    // reset view btn
    this->_components.push_back(new MaterialButton({15, 15}, "reset view", _font, []() {
        auto view = options.function.defaultView;

        view.adaptToWindowSize(options.size);
        options.view = view;
        computeTexture();
        history.clear();
    }));
    // view history btn
    this->_components.push_back(new MaterialButton({200, 15}, "go back", _font, []() {
        if (!history.empty()) {
            auto value = history.back();

            history.pop_back();
            options.view = ComplexView(value);
            computeTexture();
        }
    }));
    // build options from fractalFunctions map
    std::vector<std::string> _options;
    for (auto &item: fractalFunctions) {
        _options.push_back(item.name);
    }
    // fractal function selector
    this->_components.push_back(new MaterialSelector({357, 15}, _options, _font, [](int index) {
        options.function = fractalFunctions[index];
        auto view = options.function.defaultView;

        view.adaptToWindowSize(options.size);
        options.view = view;
        history.clear();
        computeTexture();
    }));
    // always add the view builder at the end
    this->_components.push_back(new ViewBuilder([](sf::Vector2f pos, sf::Vector2f size) {
        if (size.x < 10 || size.y < 10) return;

        history.emplace_back(options.view);
        auto currentView = options.view;
        RawView view = {
                currentView.minRe + (currentView.maxRe - currentView.minRe) * pos.x / (options.size.x - 1),
                currentView.minRe + (currentView.maxRe - currentView.minRe) * (pos.x + size.x) / (options.size.x - 1),
                currentView.minIm + (currentView.maxIm - currentView.minIm) * pos.y / (options.size.y - 1),
                currentView.minIm + (currentView.maxIm - currentView.minIm) * (pos.y + size.y) / (options.size.y - 1)
        };
        options.view = ComplexView(view);
        options.view.adaptToWindowSize(options.size);
        computeTexture();
    }));
}

void UiService::draw(sf::RenderWindow &window) {
    for (auto &component: _components) {
        component->draw(window);
    }
}

void UiService::dispatchEvent(sf::Event event) {
    for (auto &component: _components) {
        // if component return true, stop the event propagation
        if (component->handleEvent(event)) {
            break;
        }
    }
}

UiService::~UiService() {
    for (auto &component: _components) {
        delete component;
    }
}
