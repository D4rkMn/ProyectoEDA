#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>

template<typename T>
class Cluster {
private:
    std::vector<T> contenido;
    T medoid;

public:
    T& getData(int i);
    const T& getData(int i) const;
    std::vector<T>& getAllData();
    const std::vector<T>& getAllData() const;
    void setMedoid(const T& newMedoid);
    T& getMedoid();
    const T& getMedoid() const;
};

#endif