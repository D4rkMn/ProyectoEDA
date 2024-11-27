#ifndef MMR_H
#define MMR_H

#include "Algorithms/Algorithm.h"

template<typename T>
class MMR : public Algorithm<T> {
private:
    float lambda;
    float objective_function(Data<T>&, Data<T>&, std::vector<Data<T>>&) const;

public:
    MMR(std::function<float(const Data<T>&, const Data<T>&)> sim,
        std::function<float(const Data<T>&, const Data<T>&)> div,
        float lambda = 0.5f)
        : Algorithm<T>(sim, div), lambda(lambda) {}

    std::vector<Data<T>> execute(size_t k, Data<T>& q, DataSet<T>& O, std::vector<Cluster<T>>& C) override;
};

#include "Algorithms/MMR/MMR.tpp"

#endif