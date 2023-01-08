#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <thread>
#include "functions.h"
#include "complexView.h"

struct RenderData {
    std::vector<std::array<uint8_t, 4>> pixels;
    sf::Texture texture;
    sf::Sprite sprite;
};

struct RenderOptions {
    int maxIterations = fractalFunctions[0].defaultMaxIterations;
    FractalFunction &function = const_cast<FractalFunction &>(fractalFunctions[0]);
    ComplexView view = function.defaultView;
    sf::Vector2u size = {0, 0};
};

extern RenderOptions options;

extern RenderData data;

extern std::vector<ComplexView> history;
