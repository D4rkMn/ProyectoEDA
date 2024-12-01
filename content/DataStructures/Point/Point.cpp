#include "DataStructures/Point/Point.h"
#include <iostream>

Point::Point(int dim) : coordinates(dim, 0.0) {}

Point::Point(const std::vector<double>& coords) : coordinates(coords) {}

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

double Point::euclideanDistance(const Point& other) const {
    double sum = 0.0;
    for (size_t i = 0; i < coordinates.size(); ++i) {
        sum += (coordinates[i] - other.coordinates[i]) * (coordinates[i] - other.coordinates[i]);
    }
    return std::sqrt(sum);
}