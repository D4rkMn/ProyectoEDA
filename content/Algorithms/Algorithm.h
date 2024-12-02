#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "DataStructures/DataSet/DataSet.h"
#include "DataStructures/Cluster/Cluster.h"
#include "DataStructures/Data/Data.h"
#include <vector>
#include <functional>

template<typename T>
class Algorithm {
public:
    Algorithm() = default;
    virtual ~Algorithm() = default;
};

template<typename T>
class NoveltyAlgorithm : public Algorithm<T> {
protected:
    std::function<double(const Data<T>&, const Data<T>&)> distance_sim;
    std::function<double(const Data<T>&, const Data<T>&)> distance_div;
    double lambda;

public:
    NoveltyAlgorithm(std::function<double(const Data<T>&, const Data<T>&)> sim,
             std::function<double(const Data<T>&, const Data<T>&)> div,
             double _lambda){
        distance_sim = sim;
        distance_div = div;
        lambda = _lambda;
        }

    DataSet<T> calculate_query_set(DataSet<T>& O, const Data<T>& q);
    virtual std::vector<Data<T>> execute(size_t k, const Data<T>& q, DataSet<T>& O, 
                                 std::vector<Cluster<T>>& C) = 0;
};

template<typename T>
class CoverageAlgorithm : Algorithm<T> {
protected:
    std::function<double(const Data<T>&, const Data<T>&)> distance;

public:
    CoverageAlgorithm(std::function<double(const Data<T>&, const Data<T>&)> dist){
        distance = dist;
    }
    
    virtual std::vector<Data<T>> execute(size_t k, const Data<T>& q, DataSet<T>& O, 
                                 std::vector<Cluster<T>>& C, DataSet<T>& querySet) = 0;
};

#include "Algorithms/Algorithm.tpp"

#endif