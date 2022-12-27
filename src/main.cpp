#include <SFML/Graphics.hpp>
#include "fractal-playground.h"

RenderOptions options = RenderOptions();
RenderData data = RenderData();
std::atomic<bool> updatingTexture(false);

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
    if (iteration < MAX_ITERATIONS) {
        return gradient(colors[0], colors[1], (float) iteration / MAX_ITERATIONS);
    } else {
        return sf::Color::Black;
    }
}

void computeTexture() {
    updatingTexture = true;
    if (data.pixels.size() != options.size.x * options.size.y * 4) {
        data.pixels.resize(options.size.x * options.size.y * 4);
        data.texture.create(options.size.x, options.size.y);
    }
    const int chunkSize = options.size.x * options.size.y / options.threadCount;

    std::vector<std::thread> threads;
    size_t start = 0;
    double re = options.minRe;
    double im = options.minIm;
    double stepRe = (options.maxRe - options.minRe) / (options.size.x - 1);
    double stepIm = (options.maxIm - options.minIm) / (options.size.y - 1);

    for (int i = 0; i < options.threadCount; i++, start += chunkSize) {
        threads.emplace_back([&](int threadId, size_t start, size_t end) {
            size_t index = start * 4;
            int x = start % options.size.x;
            int y = start / options.size.x;

            while (start < end) {
                double complexRe = re + x * stepRe;
                double complexIm = im + y * stepIm;
                sf::Color color = mandelbrot(complexRe, complexIm);

                data.pixels[index] = color.r;
                data.pixels[index + 1] = color.g;
                data.pixels[index + 2] = color.b;
                data.pixels[index + 3] = color.a;
                start++;
                index += 4;
                x++;
                if (x >= options.size.x) {
                    x = 0;
                    y++;
                }
            }
        }, i, start, start + chunkSize);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    data.texture.update(data.pixels.data());
    updatingTexture = false;
}

void handle_window_resize(sf::RenderWindow& window) {
    options.size = window.getSize();
    options.aspectRatio = (float) options.size.x / (float) options.size.y;
    options.minIm = options.minRe / options.aspectRatio;
    options.maxIm = options.maxRe / options.aspectRatio;
}

int main() {
    std::thread updateThread(computeTexture);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My Window");
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
                uiService.dispatchEvent(event);
            }
        }
        window.clear();
        if (!updatingTexture) {
            window.draw(data.sprite);
        }
        uiService.draw(window);
        window.display();
    }
}
