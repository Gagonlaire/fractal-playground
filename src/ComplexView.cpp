#include "complex-view.h"

ComplexView::ComplexView(long double minRe, long double maxRe, long double minIm, long double maxIm) {
    this->minRe = minRe;
    this->maxRe = maxRe;
    this->minIm = minIm;
    this->maxIm = maxIm;
}

ComplexView::ComplexView(RawView rawView) {
    this->minRe = std::get<0>(rawView);
    this->maxRe = std::get<1>(rawView);
    this->minIm = std::get<2>(rawView);
    this->maxIm = std::get<3>(rawView);
}

void ComplexView::from(ComplexView other, sf::Vector2u size) {
    this->minRe = other.minRe;
    this->maxRe = other.maxRe;
    this->minIm = other.minIm;
    this->maxIm = other.maxIm;

    this->adaptToWindowSize(size);
}

void ComplexView::adaptToWindowSize(sf::Vector2u size) {
    double aspectRatio = (double) size.x / size.y;

    if (size.x > size.y) {
        long double newWidth = (maxRe - minRe) * aspectRatio;
        long double halfWidth = (newWidth - (maxRe - minRe)) / 2;
        minRe -= halfWidth;
        maxRe += halfWidth;
    } else {
        long double newHeight = (maxIm - minIm) / aspectRatio;
        long double halfHeight = (newHeight - (maxIm - minIm)) / 2;
        minIm -= halfHeight;
        maxIm += halfHeight;
    }
}

RawView ComplexView::getRawView() const {
    return std::make_tuple(minRe, maxRe, minIm, maxIm);
}
