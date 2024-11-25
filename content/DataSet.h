#ifndef DATASET_H
#define DATASET_H

#include <vector>

template<typename T>
class DataSet {
private:
    std::vector<T> content;

public:
    T& getData(int i);
    const T& getData(int i) const;
    std::vector<T>& getAllData();
    const std::vector<T>& getAllData() const;
    void addData(const T& data);
    size_t size() const;
};

#endif