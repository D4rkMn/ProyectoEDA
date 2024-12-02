#ifndef MOTLEY_H
#define MOTLEY_H

#include "Algorithms/Algorithm.h"
#include <algorithm>

template<typename T>
class Motley : public CoverageAlgorithm<T> {
private:
    double r;  // factor de ajuste

public:
    Motley(std::function<double(const Data<T>&, const Data<T>&)> dist,
            double r = 0.5f) 
        : CoverageAlgorithm<T>(dist), r(r) {}

    std::vector<Data<T>> execute(size_t k, const Data<T>& q, DataSet<T>& O, std::vector<Cluster<T>>& C, DataSet<T>& querySet) override;
};

#include "Algorithms/Motley/Motley.tpp"

#endif