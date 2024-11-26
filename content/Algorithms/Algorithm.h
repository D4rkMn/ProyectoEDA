#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "DataStructures/DataSet/DataSet.h"
#include "DataStructures/Data/Data.h"
#include "DataStructures/Cluster/Cluster.h"
#include <vector>
#include <functional>

template<typename T>
class Algorithm {
protected:
    std::function<float(const Data<T>&, const Data<T>&)> distance_sim;
    std::function<float(const Data<T>&, const Data<T>&)> distance_div; 

public:
    Algorithm(std::function<float(const Data<T>&, const Data<T>&)> sim,
             std::function<float(const Data<T>&, const Data<T>&)> div){
        distance_sim = sim;
        distance_div = div;
        }
    
    virtual std::vector<Data<T>> execute(DataSet<T>& O, 
                                 std::vector<Cluster<T>>& C, Data<T> q, int k) = 0;
};

#endif

/*

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "DataStructures/DataSet/DataSet.h"
#include "DataStructures/Cluster/Cluster.h"
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
*/