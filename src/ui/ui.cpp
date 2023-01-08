#include "ui.h"
#include "data.h"

UiService::UiService() {
    // init various resources
    this->_font.loadFromFile("resources/Roboto-Regular.ttf");

    // build main row
    auto row = new Row({0, 15}, 15, {});

    // build options from fractalFunctions map
    std::vector<std::string> _options;
    for (auto &item: fractalFunctions) {
        _options.push_back(item.name);
    }

    // create ui elements
    auto reset_btn = new MaterialButton({0, 0}, "reset view", _font, []() {
        auto view = options.function.defaultView;

        view.adaptToWindowSize(options.size);
        options.view = view;
        computeTexture();
        history.clear();
    });
    auto back_btn = new MaterialButton({0, 0}, "go back", _font, []() {
        if (!history.empty()) {
            auto value = history.back();

            history.pop_back();
            options.view = ComplexView(value);
            computeTexture();
        }
    });
    auto view_builder = new ViewBuilder([](sf::Vector2f pos, sf::Vector2f size) {
        if (std::abs(size.x) < 10 || std::abs(size.y) < 10) {
            return;
        } else if (size.x < 0) {
            pos.x += size.x;
            size.x = -size.x;
        } else if (size.y < 0) {
            pos.y += size.y;
            size.y = -size.y;
        }

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
    });
    // build the iteration box before +/- buttons to send a reference to them
    auto max_iterations = new MaterialBox({0, 0}, {100, 50}, _font,
                                          "iterations: " + std::to_string(options.maxIterations));
    auto increment_btn = new MaterialButton({0, 0}, "+", _font, [max_iterations, row]() {
        options.maxIterations += options.maxIterations * ITERATION_RATIO / 10;
        max_iterations->setText("iterations: " + std::to_string(options.maxIterations));
        row->update();
        computeTexture();
    });
    auto decrement_btn = new MaterialButton({0, 0}, "-", _font, [max_iterations, row]() {
        if (options.maxIterations > 1) {
            options.maxIterations -= options.maxIterations * ITERATION_RATIO / 10;
            max_iterations->setText("iterations: " + std::to_string(options.maxIterations));
            row->update();
            computeTexture();
        }
    });
    auto reset_iterations = new MaterialButton({0, 0}, "reset iterations", _font, [max_iterations, row]() {
        if (options.maxIterations != options.function.defaultMaxIterations) {
            options.maxIterations = options.function.defaultMaxIterations;
            max_iterations->setText("iterations: " + std::to_string(options.maxIterations));
            row->update();
            computeTexture();
        }
    });
    // the selector also need a reference to the iteration box
    auto selector = new MaterialSelector({337, 15}, _options, _font, [max_iterations, row](int index) {
        options.function = fractalFunctions[index];
        options.maxIterations = options.function.defaultMaxIterations * ITERATION_RATIO;
        max_iterations->setText("iterations: " + std::to_string(options.maxIterations));
        row->update();
        options.view = options.function.defaultView;
        options.view.adaptToWindowSize(options.size);
        history.clear();
        computeTexture();
    });

    // mount ui elements
    row->push_back({reset_btn, back_btn, selector, decrement_btn, max_iterations, increment_btn, reset_iterations,
                    view_builder});
    this->_components.push_back(row);
}

void UiService::draw(sf::RenderWindow &window) {
    for (auto &component: _components) {
        component->draw(window);
    }
}

void UiService::dispatchEvent(sf::RenderWindow &window, sf::Event event) {
    for (auto &component: _components) {
        // if component return true, stop the event propagation
        if (component->handleEvent(window, event)) {
            break;
        }
    }
}

UiService::~UiService() {
    for (auto &component: _components) {
        delete component;
    }
}
