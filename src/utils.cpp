#include "utils.h"

sf::Color gradient(const sf::Color &start, const sf::Color &end, float t) {
    sf::Color result;
    result.r = start.r + t * (end.r - start.r);
    result.g = start.g + t * (end.g - start.g);
    result.b = start.b + t * (end.b - start.b);
    return result;
}

sf::Color getColorFromIterations(int iterations) {
    return {
        static_cast<sf::Uint8>(iterations % 256),
        static_cast<sf::Uint8>((iterations * 3) % 256),
        static_cast<sf::Uint8>((iterations * 7) % 256)
    };
}
