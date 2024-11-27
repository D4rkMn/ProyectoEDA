#ifndef MOTLEY_H
#define MOTLEY_H

#include "Algorithms/Algorithm.h"

template<typename T>
class Motley : public Algorithm<T> {
private:
    float r;  // factor de ajuste

public:
    Motley(std::function<float(const Data<T>&, const Data<T>&)> sim,
             std::function<float(const Data<T>&, const Data<T>&)> div,
            float r = 0.5f) 
        : Algorithm<T>(sim, div), r(r) {}

    std::vector<Data<T>> execute(size_t k, Data<T>& q, DataSet<T>& O, std::vector<Cluster<T>>& C) override;
};

#include "Algorithms/Motley/Motley.tpp"

#endif