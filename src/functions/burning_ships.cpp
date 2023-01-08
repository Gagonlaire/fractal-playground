#include "utils.h"
#include "functions.h"

#define MAX_ITERATIONS (400 * ITERATION_RATIO)

sf::Color burning_ship(long double re, long double im) {
    long double x = 0;
    long double y = 0;
    long double new_x;
    long double new_y;
    int iteration = 0;

    while (x * x + y * y < 4 && iteration < MAX_ITERATIONS) {
        new_x = x * x - y * y + re;
        new_y = 2 * abs(x * y) + im;
        x = new_x;
        y = new_y;
        iteration++;
    }

    if (iteration == MAX_ITERATIONS) {
        return sf::Color::Black;
    } else {
        return getColorFromIterations(iteration, MAX_ITERATIONS);
    }
}
