#include "utils.h"
#include "functions.h"

sf::Color mandelbrot(long double re, long double im, int maxIterations) {
    long double zRe = re;
    long double zIm = im;
    int iterations;

    for (iterations = 0; iterations < maxIterations; iterations++) {
        if (zRe * zRe + zIm * zIm >= 4) break;

        long double zReNew = zRe * zRe - zIm * zIm + re;
        long double zImNew = 2 * zRe * zIm + im;
        zRe = zReNew;
        zIm = zImNew;
    }
    if (iterations == maxIterations) {
        return sf::Color::Black;
    }
    return getColorFromIterations(iterations, maxIterations);
}
