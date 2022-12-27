#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "utils.h"
#include "UI.h"

#define MAX_ITERATIONS 100

struct RenderOptions {
    double minRe = -2.0;
    double maxRe = 1.0;
    double minIm = -1.0;
    double maxIm = 1.0;
    size_t width = 1920;
    size_t height = 1080;
    std::vector<sf::Color> colors = {
            {38, 70, 83},
            {231, 111, 81}
    };
};

struct FractalFunction {
    std::function<sf::Color(double, double, const RenderOptions&)> function;
};

static RenderOptions renderOptions = RenderOptions();

static const std::unordered_map<std::string, FractalFunction> fractalFunctions = {};
