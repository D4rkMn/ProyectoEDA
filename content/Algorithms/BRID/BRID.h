#ifndef BRID_H
#define BRID_H

#include "Algorithms/Algorithm.h"

template<typename T>
class BRID : public Algorithm<T> {
public:
    BRID(std::function<float(const Data<T>&, const Data<T>&)> sim,
        std::function<float(const Data<T>&, const Data<T>&)> div)
        : Algorithm<T>(sim, div) {}

    std::vector<Data<T>> execute(DataSet<T>& O, std::vector<Cluster<T>>& C, Data<T> q, int k) override;
};

#include "Algorithms/BRID/BRID.tpp"

#endif