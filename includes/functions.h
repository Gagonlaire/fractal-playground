#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <complex>
#include "utils.h"
#include "enum.h"

struct FractalFunction {
    std::function<sf::Color(double, double)> function;
};

sf::Color mandelbrot(double re, double im);
sf::Color mandlebar(double re, double im);
sf::Color burning_ship(double re, double im);
sf::Color julia(double re, double im);

static const std::map<std::string, FractalFunction> fractalFunctions = {
        {"mandelbrot", {mandelbrot}},
        {"mandlebar", {mandlebar}},
        {"burning_ship", {burning_ship}},
        {"julia", {julia}}
};
