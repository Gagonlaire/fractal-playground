#include "data.h"
#include "ui.h"
#include "utils.h"
#include <array>

RenderOptions options;
RenderData data;
std::vector<ComplexView> history;

void handle_window_resize(sf::RenderWindow &window) {
    options.size = window.getSize();
    data.pixels.resize(options.size.x * options.size.y);
    data.texture.create(options.size.x, options.size.y);
    options.view.adaptToWindowSize(options.size);
}

void computeTexture() {
    long double re = options.view.minRe;
    long double im = options.view.minIm;
    long double stepRe = (options.view.maxRe - options.view.minRe) / (options.size.x - 1);
    long double stepIm = (options.view.maxIm - options.view.minIm) / (options.size.y - 1);

    parallelForEach(data.pixels.begin(), data.pixels.end(), [&](auto &pixel, size_t index) {
        int x = index % options.size.x;
        int y = index / options.size.x;
        long double complexRe = re + x * stepRe;
        long double complexIm = im + y * stepIm;

        sf::Color color = options.function.function(complexRe, complexIm, options.maxIterations);
        pixel = {color.r, color.g, color.b, color.a};
    });

    data.texture.update((uint8_t *) data.pixels.data());
}

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Fractal Playground");
    UiService uiService = UiService();

    window.setFramerateLimit(60);
    handle_window_resize(window);
    computeTexture();
    data.sprite.setTexture(data.texture);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                handle_window_resize(window);
                computeTexture();
            } else {
                uiService.dispatchEvent(window, event);
            }
        }
        window.draw(data.sprite);
        uiService.draw(window);
        window.display();
    }
}
