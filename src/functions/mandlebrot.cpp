#include "utils.h"

#define ITERATION_RATIO 1
#define MAX_ITERATIONS (300 * ITERATION_RATIO)

sf::Color mandelbrot(long double re, long double im) {
    long double zRe = re;
    long double zIm = im;
    int iterations;

    for (iterations = 0; iterations < MAX_ITERATIONS; iterations++) {
        if (zRe * zRe + zIm * zIm >= 4) break;

        long double zReNew = zRe * zRe - zIm * zIm + re;
        long double zImNew = 2 * zRe * zIm + im;
        zRe = zReNew;
        zIm = zImNew;
    }
    if (iterations == MAX_ITERATIONS) {
        return sf::Color::Black;
    }
    return getColorFromIterations(iterations);
}
