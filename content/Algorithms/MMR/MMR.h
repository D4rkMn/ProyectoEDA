#ifndef MMR_H
#define MMR_H

#include "Algorithms/Algorithm.h"

template<typename T>
class MMR : public Algorithm<T> {
private:
    float lambda;

public:
    MMR(std::function<float(const Data<T>&, const Data<T>&)> sim,
        std::function<float(const Data<T>&, const Data<T>&)> div
        float lambda = 0.5f)
        : Algorithm<T>(sim, div), lambda(lambda) {}

    std::vector<Data<T>> execute(DataSet<T>& O, std::vector<Cluster<T>>& C, Data<T> q, int k) override;
};

#include "Algorithms/MMR/MMR.tpp"

#endif