#include "functions.h"

sf::Color julia(double re, double im) {
    std::complex<long double> c(-0.8, 0.156);
    std::complex<long double> z(re, im);

    int iterations = 0;
    while (iterations < 300 && std::abs(z) < 2) {
        z = z * z + c;
        iterations++;
    }

    if (iterations == 300) {
        return sf::Color::Black;
    }
    return getColorFromIterations(iterations);
}
