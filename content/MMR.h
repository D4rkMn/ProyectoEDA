#ifndef MMR_H
#define MMR_H

#include "Algorithm.h"

template<typename T>
class MMR : public Algorithm<T> {
private:
    float lambda;

public:
    MMR(std::function<float(const T&, const T&)> sim,
        std::function<float(const T&, const T&)> div,
        float lambda = 0.5f)
        : Algorithm<T>(sim, div), lambda(lambda) {}

    std::vector<T> execute(DataSet<T>& O, std::vector<Cluster<T>>& C) override {
        // TODO: Implementar el algoritmo MMR
        return std::vector<T>();
    }
};

#endif