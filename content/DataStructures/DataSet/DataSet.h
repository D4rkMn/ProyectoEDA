#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include "DataStructures/Data/Data.h"
#include <cstddef>

template<typename T>
class DataSet {
private:
    std::vector<Data<T>> content; 

public:
    Data<T>& getData(int i);
    const Data<T>& getData(int i) const;
    std::vector<Data<T>>& getAllData();
    const std::vector<Data<T>>& getAllData() const;
    void addData(const Data<T>& data);
    size_t size() const;
};

#include "DataStructures/DataSet/DataSet.tpp"

#endif