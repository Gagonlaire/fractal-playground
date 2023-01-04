#pragma once

#include <SFML/Graphics.hpp>
#include <complex>
#include "utils.h"
#include "complex-view.h"

struct FractalFunction {
    std::string name;
    ComplexView defaultView;
    std::function<sf::Color(long double, long double)> function;
};

sf::Color mandelbrot(long double, long double);
sf::Color mandlebar(long double, long double);
sf::Color burning_ship(long double, long double);
sf::Color julia(long double, long double);

static const std::vector<FractalFunction> fractalFunctions = {
        {"mandelbrot", {-2, 1, -1.5, 1.5}, mandelbrot},
        {"mandlebar", {-2.1, 2.1, -2.1, 2.1}, mandlebar},
        {"burning_ship", {-2.5, 1.5, -1.6, 1.6}, burning_ship},
        {"julia", {-1.5, 1.5, -1.5, 1.5}, julia}
};
