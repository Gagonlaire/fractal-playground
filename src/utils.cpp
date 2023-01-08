#include "utils.h"
#include <cmath>

sf::Color getColorFromIterations(int iterations, int maxIterations) {
    float ratio = static_cast<float>(iterations) / static_cast<float>(maxIterations);
    auto red = static_cast<sf::Uint8>(128.0f + 127.0f * std::sin(6.28318f * (ratio + 0.75f)));
    auto green = static_cast<sf::Uint8>(128.0f + 127.0f * std::sin(6.28318f * (ratio + 0.5f)));
    auto blue = static_cast<sf::Uint8>(128.0f + 127.0f * std::sin(6.28318f * (ratio + 0.25f)));

    return {red, green, blue};
}
