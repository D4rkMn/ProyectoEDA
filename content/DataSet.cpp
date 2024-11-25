#include "DataSet.h"

template<typename T>
T& DataSet<T>::getData(int i) {
    return content[i];
}

template<typename T>
const T& DataSet<T>::getData(int i) const {
    return content[i];
}

template<typename T>
std::vector<T>& DataSet<T>::getAllData() {
    return content;
}

template<typename T>
const std::vector<T>& DataSet<T>::getAllData() const {
    return content;
}

template<typename T>
void DataSet<T>::addData(const T& data) {
    content.push_back(data);
}

template<typename T>
size_t DataSet<T>::size() const {
    return content.size();
}