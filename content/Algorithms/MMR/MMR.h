#ifndef MMR_H
#define MMR_H

#include "Algorithms/Algorithm.h"

template<typename T>
class MMR : public NoveltyAlgorithm<T> {
private:
    double objective_function(const Data<T>&, const Data<T>&, std::vector<Data<T>>&) const;

public:
    MMR(std::function<double(const Data<T>&, const Data<T>&)> sim,
        std::function<double(const Data<T>&, const Data<T>&)> div,
        double lambda = 0.5f)
        : NoveltyAlgorithm<T>(sim, div, lambda) {}

    std::vector<Data<T>> execute(size_t k, const Data<T>& q, DataSet<T>& O, std::vector<Cluster<T>>& C) override;
};

#include "Algorithms/MMR/MMR.tpp"

#endif