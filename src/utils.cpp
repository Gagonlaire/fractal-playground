#include "utils.h"

sf::Color getColorFromIterations(int iterations) {
    return {
        static_cast<sf::Uint8>(iterations % 256),
        static_cast<sf::Uint8>((iterations * 3) % 256),
        static_cast<sf::Uint8>((iterations * 7) % 256)
    };
}
