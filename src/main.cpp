#include "data.h"
#include "UI.h"
#include "fractal-playground.h"

RenderOptions options = RenderOptions();
RenderData data = RenderData();
auto history = std::vector<ComplexView>();

void handle_window_resize(sf::RenderWindow &window) {
    options.size = window.getSize();
    options.view.adaptToWindowSize(options.size);
}

void computeTexture() {
    if (data.pixels.size() != options.size.x * options.size.y * 4) {
        data.pixels.resize(options.size.x * options.size.y * 4);
        data.texture.create(options.size.x, options.size.y);
    }
    const int chunkSize = options.size.x * options.size.y / options.threadCount;
    std::vector<std::thread> threads;
    size_t start = 0;
    long double re = options.view.minRe;
    long double im = options.view.minIm;
    long double stepRe = (options.view.maxRe - options.view.minRe) / (options.size.x - 1);
    long double stepIm = (options.view.maxIm - options.view.minIm) / (options.size.y - 1);

    for (int i = 0; i < options.threadCount; i++, start += chunkSize) {
        threads.emplace_back([&](int threadId, size_t start, size_t end) {
            size_t index = start * 4;
            int x = start % options.size.x;
            int y = start / options.size.x;

            while (start < end) {
                long double complexRe = re + x * stepRe;
                long double complexIm = im + y * stepIm;
                sf::Color color = options.function.function(complexRe, complexIm);

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

    for (auto &thread: threads) {
        thread.join();
    }

    data.texture.update(data.pixels.data());
}

int main() {
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
                std::cout << "window resized" << std::endl;
                handle_window_resize(window);
                computeTexture();
            } else {
                uiService.dispatchEvent(event);
            }
        }
        window.draw(data.sprite);
        uiService.draw(window);
        window.display();
    }
}
