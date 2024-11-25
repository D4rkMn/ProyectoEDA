#ifndef BRID_H
#define BRID_H

#include "Algorithm.h"

template<typename T>
class BRID : public Algorithm<T> {
public:
    BRID(std::function<float(const T&, const T&)> sim,
         std::function<float(const T&, const T&)> div)
        : Algorithm<T>(sim, div) {}

    std::vector<T> execute(DataSet<T>& O, std::vector<Cluster<T>>& C) override {
        // TODO: Implementar el algoritmo BRID
        return std::vector<T>();
    }
};

#endif