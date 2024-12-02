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

double Point::cosineSimilarity(const Point& other) const {
    if (coordinates.size() != other.coordinates.size()) {
        throw std::invalid_argument("Points must have the same dimensions.");
    }

    double dotProduct = 0.0;
    double magnitudeA = 0.0;
    double magnitudeB = 0.0;

    for (size_t i = 0; i < coordinates.size(); ++i) {
        dotProduct += coordinates[i] * other.coordinates[i];
        magnitudeA += coordinates[i] * coordinates[i];
        magnitudeB += other.coordinates[i] * other.coordinates[i];
    }

    if (magnitudeA == 0.0 || magnitudeB == 0.0) {
        throw std::invalid_argument("Cannot calculate cosine similarity with zero magnitude.");
    }

    return dotProduct / (std::sqrt(magnitudeA) * std::sqrt(magnitudeB));
}