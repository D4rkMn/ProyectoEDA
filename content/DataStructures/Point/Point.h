#ifndef POINT_H
#define POINT_H

#include <vector>
#include <cmath>

class Point {
public:
    std::vector<double> coordinates;

    Point(int dim = 0);
    Point(const std::vector<double>& coords);
    void print() const;
    std::vector<double>& getCoordinates();
    const std::vector<double>& getCoordinates() const;
    double euclideanDistance(const Point& other) const;
    double cosineSimilarity(const Point& other) const;
};

#endif
