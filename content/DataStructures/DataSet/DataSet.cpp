#include "DataStructures/DataSet/DataSet.h"

template<typename T>

Data<T>& DataSet<T>::getData(int i) {
    return content[i];
}

template<typename T>
const Data<T>& DataSet<T>::getData(int i) const {
    return content[i];
}

template<typename T>
std::vector<Data<T>>& DataSet<T>::getAllData() {
    return content;
}

template<typename T>
const std::vector<Data<T>>& DataSet<T>::getAllData() const {
    return content;
}

template<typename T>
void DataSet<T>::addData(const Data<T>& data) {
    content.push_back(data);
}

template<typename T>
size_t DataSet<T>::size() const {
    return content.size();
}