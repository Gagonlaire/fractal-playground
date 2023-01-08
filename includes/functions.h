#pragma once

#include <SFML/Graphics.hpp>
#include <complex>
#include "utils.h"
#include "complexView.h"

// Change this value to reduce the max_iterations, improve performance
#define ITERATION_RATIO 1

void computeTexture();

struct FractalFunction {
    std::string name;
    ComplexView defaultView;
    std::function<sf::Color(long double, long double)> function;
};

sf::Color mandelbrot(long double, long double);
sf::Color mandlebar(long double, long double);
sf::Color burning_ship(long double, long double);
sf::Color julia_1(long double, long double);
sf::Color julia_2(long double, long double);
sf::Color julia_3(long double, long double);

static const std::vector<FractalFunction> fractalFunctions = {
        {"mandelbrot", {-2.8, 1.8, -2.3, 2.3}, mandelbrot},
        {"mandlebar", {-2.7, 2.7, -2.7, 2.7}, mandlebar},
        {"burning ship", {-2.6, 1.6, -2.2, 1.2}, burning_ship},
        {"julia 1", {-1.7, 1.7, -1.7, 1.7}, julia_1},
        {"julia 2", {-1.7, 1.7, -1.7, 1.7}, julia_2},
        {"julia 3", {-1.7, 1.7, -1.7, 1.7}, julia_3},
};
