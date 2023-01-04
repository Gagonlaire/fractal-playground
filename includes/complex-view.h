#pragma once

#include <SFML/Graphics.hpp>
#include <tuple>

typedef std::tuple<long double, long double, long double, long double> RawView;

class ComplexView {
public:
    long double minRe;
    long double maxRe;
    long double minIm;
    long double maxIm;

public:
    ComplexView(long double, long double, long double, long double);

    explicit ComplexView(RawView);

    void adaptToWindowSize(sf::Vector2u);

    void from(ComplexView, sf::Vector2u);

    RawView getRawView() const;

    ComplexView& operator=(const ComplexView& other) = default;
};
