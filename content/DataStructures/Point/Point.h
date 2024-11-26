#ifndef POINT_H
#define POINT_H

#include <vector>

class Point {
private:
    std::vector<double> coordinates;

public:
    Point(int dim = 0);
    void print() const;
    std::vector<double>& getCoordinates();
    const std::vector<double>& getCoordinates() const;
};

#endif