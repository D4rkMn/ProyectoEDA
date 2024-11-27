#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <cstddef>
#include "DataStructures/Data/Data.h"

template<typename T>
class Cluster {
private:
    std::vector<Data<T>> content;
    Data<T> medoid;

public:
    Data<T>& getData(int i);
    const Data<T>& getData(int i) const;
    std::vector<Data<T>>& getAllData();
    const std::vector<Data<T>>& getAllData() const;
    void setMedoid(const Data<T>& newMedoid);
    Data<T>& getMedoid();
    const Data<T>& getMedoid() const;
    void addData(const Data<T>& data);
    size_t size() const;
};

#include "DataStructures/Cluster/Cluster.tpp"

#endif