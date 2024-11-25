#ifndef SWAP_H
#define SWAP_H

#include "Algorithms/Algorithm.h"

template<typename T>
class Swap : public Algorithm<T> {
private:
    float lambda;

public:
    Swap(std::function<float(const T&, const T&)> sim,
         std::function<float(const T&, const T&)> div,
         float lambda = 0.5f)
        : Algorithm<T>(sim, div), lambda(lambda) {}

    std::vector<T> execute(DataSet<T>& O, std::vector<Cluster<T>>& C) override;
    float func() const;
};

#include "Algorithms/Swap/Swap.tpp"

#endif