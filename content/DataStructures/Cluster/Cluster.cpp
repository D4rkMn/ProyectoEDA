
#include "DataStructures/Cluster/Cluster.h"


template<typename T>
Data<T>& Cluster<T>::getData(int i) {
    return content[i];
}

template<typename T>
const Data<T>& Cluster<T>::getData(int i) const {
    return content[i];
}

template<typename T>
std::vector<Data<T>>& Cluster<T>::getAllData() {
    return content;
}

template<typename T>
const std::vector<Data<T>>& Cluster<T>::getAllData() const {
    return content;
}

template<typename T>
void Cluster<T>::setMedoid(const Data<T>& newMedoid) {
    medoid = newMedoid;
}

template<typename T>
Data<T>& Cluster<T>::getMedoid() {
    return medoid;
}

template<typename T>
const Data<T>& Cluster<T>::getMedoid() const {
    return medoid;
}

template<typename T>
void Cluster<T>::addData(const Data<T>& data) {
    content.push_back(data);
}

template<typename T>
size_t Cluster<T>::size() const {
    return content.size();
}