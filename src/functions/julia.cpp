#include "functions.h"

#define MAX_ITERATIONS (400 * ITERATION_RATIO)

sf::Color julia(long double re, long double im, long double cRe, long double cIm) {
    std::complex<long double> c(cRe, cIm);
    std::complex<long double> z(re, im);
    int iterations = 0;

    while (iterations < 300 && std::abs(z) < 2) {
        z = z * z + c;
        iterations++;
    }
    if (iterations == 300) {
        return sf::Color::Black;
    }
    return getColorFromIterations(iterations, MAX_ITERATIONS);
}

sf::Color julia_1(long double re, long double im) {
    return julia(re, im, -0.8, 0.156);
}

sf::Color julia_2(long double re, long double im) {
    return julia(re, im, -0.7269, 0.1889);
}

sf::Color julia_3(long double re, long double im) {
    return julia(re, im, -0.4, -0.6);
}
