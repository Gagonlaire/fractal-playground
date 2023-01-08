#include "functions.h"
#include "utils.h"

sf::Color mandlebar(long double re, long double im, int maxIterations) {
    long double x = 0;
    long double y = 0;
    long double new_x;
    long double new_y;
    int iteration = 0;

    while (x * x + y * y < 4 && iteration < maxIterations) {
        new_x = x * x - y * y + re;
        new_y = -2 * x * y + im;
        x = new_x;
        y = new_y;
        iteration++;
    }

    if (iteration == 200) {
        return sf::Color::Black;
    }
    return getColorFromIterations(iteration, maxIterations);
}
