#include "Cluster.h"

template<typename T>
T& Cluster<T>::getData(int i) {
    // TODO: Implementar validación de índices
    return contenido[i];
}

template<typename T>
const T& Cluster<T>::getData(int i) const {
    // TODO: Implementar validación de índices
    return contenido[i];
}

template<typename T>
std::vector<T>& Cluster<T>::getAllData() {
    return contenido;
}

template<typename T>
const std::vector<T>& Cluster<T>::getAllData() const {
    return contenido;
}

template<typename T>
void Cluster<T>::setMedoid(const T& newMedoid) {
    // TODO: Implementar la actualización del medoide
    medoid = newMedoid;
}

template<typename T>
T& Cluster<T>::getMedoid() {
    return medoid;
}

template<typename T>
const T& Cluster<T>::getMedoid() const {
    return medoid;
}