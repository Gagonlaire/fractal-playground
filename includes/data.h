#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <thread>
#include "functions.h"
#include "complex-view.h"

struct RenderData {
    std::vector<sf::Uint8> pixels;
    sf::Texture texture;
    sf::Sprite sprite;
};

struct RenderOptions {
    size_t threadCount = std::thread::hardware_concurrency() - 1;
    FractalFunction &function = const_cast<FractalFunction &>(fractalFunctions[0]);
    ComplexView view = function.defaultView;
    sf::Vector2u size = {0, 0};
};

extern RenderOptions options;

extern RenderData data;

extern std::vector<ComplexView> history;
