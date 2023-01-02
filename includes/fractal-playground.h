#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <thread>
#include <tuple>

#define ITERATION_RATIO 1

class ComplexView {
    double long minRe;
    double long maxRe;
    double long minIm;
    double long maxIm;

public:
    ComplexView(std::tuple<double long, double long, double long, double long> data) {
        this->minRe = std::get<0>(data);
        this->maxRe = std::get<1>(data);
        this->minIm = std::get<2>(data);
        this->maxIm = std::get<3>(data);
    }
};

void computeTexture();
