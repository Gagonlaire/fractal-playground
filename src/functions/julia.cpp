#include "functions.h"

sf::Color julia(long double re, long double im, long double cRe, long double cIm, int maxIterations) {
    std::complex<long double> c(cRe, cIm);
    std::complex<long double> z(re, im);
    int iterations = 0;

    while (iterations < maxIterations && std::abs(z) < 2) {
        z = z * z + c;
        iterations++;
    }
    if (iterations == maxIterations) {
        return sf::Color::Black;
    }
    return getColorFromIterations(iterations, maxIterations);
}

sf::Color julia_1(long double re, long double im, int maxIterations) {
    return julia(re, im, -0.8, 0.156, maxIterations);
}

sf::Color julia_2(long double re, long double im, int maxIterations) {
    return julia(re, im, -0.7269, 0.1889, maxIterations);
}

sf::Color julia_3(long double re, long double im, int maxIterations) {
    return julia(re, im, -0.4, -0.6, maxIterations);
}
