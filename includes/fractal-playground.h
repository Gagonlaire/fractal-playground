#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <algorithm>
#include <execution>
#include <iostream>
#include <thread>
#include "utils.h"
#include "UI.h"

#define MAX_ITERATIONS 100

struct RenderData {
    std::vector<sf::Uint8> pixels;
    sf::Texture texture;
    sf::Sprite sprite;
};

struct RenderOptions {
    size_t threadCount = std::thread::hardware_concurrency();
    double minRe = -2.0;
    double maxRe = 2.0;
    double minIm = -1.0;
    double maxIm = 1.0;
    double aspectRatio = 1.0;
    sf::Vector2u size = {0, 0};
};

struct FractalFunction {
    std::function<sf::Color(double, double, const RenderOptions &)> function;
};

static const std::unordered_map<std::string, FractalFunction> fractalFunctions = {};

extern RenderOptions options;

extern RenderData data;

void computeTexture();
