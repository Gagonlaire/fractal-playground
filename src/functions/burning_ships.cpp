#include "functions.h"

sf::Color burning_ship(double re, double im) {
    double x = 0;
    double y = 0;
    double new_x;
    double new_y;
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
        return getColorFromIterations(iteration);
    }
}
