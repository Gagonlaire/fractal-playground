#pragma once

#include <SFML/Graphics.hpp>

/*
 * @brief Calculate the gradient color between two colors given a value between 0 and 1
 * @param start The start color
 * @param end The end color
 * @param t The value between 0 and 1
 */
sf::Color gradient(const sf::Color &start, const sf::Color &end, float t);
