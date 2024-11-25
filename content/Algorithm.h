#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "DataSet.h"
#include "Cluster.h"
#include <vector>
#include <functional>

template<typename T>
class Algorithm {
protected:
    std::function<float(const T&, const T&)> distance_sim;
    std::function<float(const T&, const T&)> distance_div;

public:
    Algorithm(std::function<float(const T&, const T&)> sim,
             std::function<float(const T&, const T&)> div){}
    
    virtual std::vector<T> execute(DataSet<T>& O, 
                                 std::vector<Cluster<T>>& C) = 0;
};

#endif