#ifndef METRIC_H
#define METRIC_H

#include "DataStructures/DataSet/DataSet.h"
#include "DataStructures/Cluster/Cluster.h"
#include <functional>
#include <vector>

template<typename T>
class Metric {
protected:
    std::function<float(const T&, const T&)> distance_sim;
    std::function<float(const T&, const T&)> distance_div;

public:
    Metric(std::function<float(const T&, const T&)> sim,
             std::function<float(const T&, const T&)> div){}

    virtual float execute(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C) = 0;
};

#endif