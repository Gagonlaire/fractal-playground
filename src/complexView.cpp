#include "complexView.h"

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
    long double width = this->maxRe - this->minRe;
    long double height = this->maxIm - this->minIm;
    long double aspectRatio = (long double) size.x / size.y;

    if (width / height > aspectRatio) {
        long double newWidth = height * aspectRatio;
        long double diff = (width - newWidth) / 2;
        this->minRe += diff;
        this->maxRe -= diff;
    } else {
        long double newHeight = width / aspectRatio;
        long double diff = (height - newHeight) / 2;
        this->minIm += diff;
        this->maxIm -= diff;
    }
}

RawView ComplexView::getRawView() const {
    return std::make_tuple(minRe, maxRe, minIm, maxIm);
}
