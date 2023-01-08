#include "utils.h"
#include "functions.h"

sf::Color burning_ship(long double re, long double im, int maxIterations) {
    long double x = 0;
    long double y = 0;
    long double new_x;
    long double new_y;
    int iteration = 0;

    while (x * x + y * y < 4 && iteration < maxIterations) {
        new_x = x * x - y * y + re;
        new_y = 2 * abs(x * y) + im;
        x = new_x;
        y = new_y;
        iteration++;
    }

    if (iteration == maxIterations) {
        return sf::Color::Black;
    }
    return getColorFromIterations(iteration, maxIterations);
}
