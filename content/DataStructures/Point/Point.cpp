#include "DataStructures/Point/Point.h"
#include <iostream>

Point::Point(int dim) : coordinates(dim, 0.0) {}

void Point::print() const {
    for (const auto& coord : coordinates) {
        std::cout << coord << " ";
    }
    std::cout << std::endl;
}

std::vector<double>& Point::getCoordinates() {
    return coordinates;
}

const std::vector<double>& Point::getCoordinates() const {
    return coordinates;
}