#ifndef BRID_H
#define BRID_H

#include "Algorithms/Algorithm.h"

template<typename T>
class BRID : public Algorithm<T> {
public:
    BRID(std::function<double(const Data<T>&, const Data<T>&)> sim,
        std::function<double(const Data<T>&, const Data<T>&)> div)
        : Algorithm<T>(sim, div) {}

    std::vector<Data<T>> execute(size_t k, const Data<T>& q, DataSet<T>& O, std::vector<Cluster<T>>& C) override;
};

#include "Algorithms/BRID/BRID.tpp"

#endif