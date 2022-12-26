#include <SFML/Graphics.hpp>
#include "fractal-playground.h"
#include <iostream>

double minRe = -2.0;
double maxRe = 1.0;
double minIm = -1.0;
double maxIm = 1.0;

std::vector<sf::Color> colors = {
        {38,  70,  83},
        {231, 111, 81}
};

sf::Color mandelbrot(double x, double y, int maxIterations) {
    double re = minRe + (maxRe - minRe) * x / (renderOptions.width - 1);
    double im = minIm + (maxIm - minIm) * y / (renderOptions.height - 1);

    double zRe = re;
    double zIm = im;
    int iteration = 0;
    while (iteration < 100 && zRe * zRe + zIm * zIm < 4) {
        double zReNew = zRe * zRe - zIm * zIm + re;
        double zImNew = 2 * zRe * zIm + im;
        zRe = zReNew;
        zIm = zImNew;
        iteration++;
    }
    if (iteration < 100) {
        return gradient(colors[0], colors[1], (float) iteration / 100);
    } else {
        return sf::Color::Black;
    }
}

void computeTexture(std::vector<sf::Uint8> &pixels, sf::Texture &texture, bool reallocate = false) {
    if (reallocate) {
        pixels.resize(renderOptions.width * renderOptions.height * 4);
        texture.create(renderOptions.width, renderOptions.height);
    }

    for (int x = 0; x < renderOptions.width; x++) {
        for (int y = 0; y < renderOptions.height; y++) {
            sf::Color color = mandelbrot(x, y, 100);
            size_t index = (x + y * renderOptions.width) * 4;

            pixels[index] = color.r;
            pixels[index + 1] = color.g;
            pixels[index + 2] = color.b;
            pixels[index + 3] = color.a;
        }
    }
    texture.update(pixels.data());
}

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My Window");
    UiService uiService = UiService();
    sf::Texture fractalTexture;
    sf::Sprite fractal;
    std::vector<sf::Uint8> pixels;

    renderOptions.width = window.getSize().x;
    renderOptions.height = window.getSize().y;
    computeTexture(pixels, fractalTexture, true);
    fractal.setTexture(fractalTexture);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                renderOptions.width = event.size.width;
                renderOptions.height = event.size.height;
                computeTexture(pixels, fractalTexture, true);
            } else {
                uiService.dispatchEvent(event);
            }
        }
        window.clear();
        window.draw(fractal);
        uiService.draw(window);
        window.display();
    }
}
