#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <thread>

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
    FractalFunction &function = const_cast<FractalFunction &>(fractalFunctions.at("mandelbrot"));
    sf::Vector2u size = {0, 0};
};

extern RenderOptions options;

extern RenderData data;
