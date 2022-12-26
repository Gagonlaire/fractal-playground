#include <SFML/Graphics.hpp>

const double minRe = -2.0;
const double maxRe = 1.0;
const double minIm = -1.0;
const double maxIm = 1.0;
int width = 1920;
int height = 1080;

std::vector<sf::Color> colors = {
        {35, 25, 66},
        {224, 177, 203}
};


sf::Color gradient(const sf::Color& start, const sf::Color& end, float t)
{
    // Clamp t between 0 and 1
    t = std::max(0.0f, std::min(1.0f, t));

    // Calculate the gradient color
    sf::Color result;
    result.r = start.r + t * (end.r - start.r);
    result.g = start.g + t * (end.g - start.g);
    result.b = start.b + t * (end.b - start.b);
    result.a = start.a + t * (end.a - start.a);
    return result;
}

sf::Color mandelbrot(double x, double y, int maxIterations)
{
    double re = minRe + (maxRe - minRe) * x / (width - 1);
    double im = minIm + (maxIm - minIm) * y / (height - 1);

    double zRe = re;
    double zIm = im;
    int iteration = 0;
    while (iteration < 100 && zRe * zRe + zIm * zIm < 4)
    {
        double zReNew = zRe * zRe - zIm * zIm + re;
        double zImNew = 2 * zRe * zIm + im;
        zRe = zReNew;
        zIm = zImNew;
        iteration++;
    }
    if (iteration < 100)
        return gradient(colors[0], colors[1], (float)iteration / maxIterations);
    else
        return sf::Color::Black;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My Window");
    sf::Image image;
    width = window.getSize().x;
    height = window.getSize().y;

    image.create(width, height);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            image.setPixel(x, y, mandelbrot(x, y, 100));
        }
    }
    sf::Texture texture;
    texture.loadFromImage(image);

    // Create a sprite from the texture
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event{};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                width = event.size.width;
                height = event.size.height;
                image.create(width, height);
                for (int x = 0; x < width; x++)
                {
                    for (int y = 0; y < height; y++)
                    {
                        image.setPixel(x, y, mandelbrot(x, y, 100));
                    }
                }
                texture.loadFromImage(image);
                sprite.setTexture(texture);
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}
