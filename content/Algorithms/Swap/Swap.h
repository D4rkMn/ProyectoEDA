#ifndef SWAP_H
#define SWAP_H

#include "Algorithms/Algorithm.h"

template<typename T>
class Swap : public Algorithm<T> {
private:
    float lambda;
    float objective_function(const T&, const T&, std::vector<T>&) const;
    std::vector<T> kNN(size_t k, const T& o_q, DataSet<T>& O) const;

public:
    Swap(std::function<float(const T&, const T&)> sim,
         std::function<float(const T&, const T&)> div,
         float lambda = 0.5f)
        : Algorithm<T>(sim, div), lambda(lambda) {}

    std::vector<T> execute(size_t k, const T& o_q, DataSet<T>& O, std::vector<Cluster<T>>& C) override;
};

#include "Algorithms/Swap/Swap.tpp"

#endif