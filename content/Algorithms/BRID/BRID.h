#ifndef BRID_H
#define BRID_H

#include "Algorithms/Algorithm.h"

template<typename T>
class BRID : public Algorithm<T> {
public:
    BRID(std::function<float(const Data<T>&, const Data<T>&)> sim,
        std::function<float(const Data<T>&, const Data<T>&)> div)
        : Algorithm<T>(sim, div) {}

    std::vector<Data<T>> execute(size_t k, Data<T>& q, DataSet<T>& O, std::vector<Cluster<T>>& C) override;
};

#include "Algorithms/BRID/BRID.tpp"

#endif