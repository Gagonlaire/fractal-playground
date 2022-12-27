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
    FractalFunction &function = const_cast<FractalFunction &>(fractalFunctions[0]);
    long double minRe = std::get<0>(function.defaultView);
    long double maxRe = std::get<1>(function.defaultView);
    long double minIm = std::get<2>(function.defaultView);
    long double maxIm = std::get<3>(function.defaultView);
    sf::Vector2u size = {0, 0};
};

extern RenderOptions options;

extern RenderData data;

typedef std::tuple<long double, long double, long double, long double> View;

typedef std::vector<View> ViewHistory;

extern ViewHistory history;
