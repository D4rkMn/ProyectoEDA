#ifndef BRID_H
#define BRID_H

#include "Algorithms/Algorithm.h"
#include <vector>
#include <set>
#include <limits>
#include <cstddef>

template<typename T>
class BRID : public CoverageAlgorithm<T> {
public:
    BRID(std::function<double(const Data<T>&, const Data<T>&)> dist)
        : CoverageAlgorithm<T>(dist) {}

    double influence(const Data<T>& a, const Data<T>& b);   
     
    std::vector<Data<T>> execute(size_t k, const Data<T>& q, DataSet<T>& O,
                std::vector<Cluster<T>>& C, DataSet<T>& query_set) override;
};

#include "Algorithms/BRID/BRID.tpp"

#endif