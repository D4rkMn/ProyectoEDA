#ifndef MONTLEY_H
#define MONTLEY_H

#include "Algorithm.h"

template<typename T>
class Montley : public Algorithm<T> {
private:
    float r;  // factor de ajuste

public:
    Montley(std::function<float(const T&, const T&)> sim,
            std::function<float(const T&, const T&)> div,
            float r = 0.5f) 
        : Algorithm<T>(sim, div), r(r) {}

    std::vector<T> execute(DataSet<T>& O, std::vector<Cluster<T>>& C) override {
        // TODO: Implementar el algoritmo Montley
        return std::vector<T>();
    }
};

#endif