#ifndef SIL_H
#define SIL_H

#include "Metric/Metric.h"

template<typename T>
class Sil : public Metric<T> {
public:
    Sil(std::function<float(const T&, const T&)> sim,
             std::function<float(const T&, const T&)> div)
        : Metric<T>(sim, div){}

    float execute(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C) override;
};

#endif