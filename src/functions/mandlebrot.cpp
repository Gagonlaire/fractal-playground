#include "functions.h"

std::vector<sf::Color> colors = {
        {38,  70,  83},
        {231, 111, 81}
};

sf::Color mandelbrot(double re, double im) {
    double zRe = re;
    double zIm = im;
    int iteration;

    for (iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
        if (zRe * zRe + zIm * zIm >= 4) break;

        double zReNew = zRe * zRe - zIm * zIm + re;
        double zImNew = 2 * zRe * zIm + im;
        zRe = zReNew;
        zIm = zImNew;
    }
    if (iteration == MAX_ITERATIONS) {
        return sf::Color::Black;
    }
    return getColorFromIterations(iteration);
}
