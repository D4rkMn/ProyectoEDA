#include "Algorithms/BRID/BRID.h"

template<typename T>
double BRID<T>::influence(const Data<T>& a, const Data<T>& b) {
    double distance = this->distance(a, b);

    if (distance == 0) {
        return 1;
    }

    return 1 / distance;
}

template<typename T>
std::vector<Data<T>> BRID<T>::execute(size_t k, const Data<T>& q, DataSet<T>& O,
std::vector<Cluster<T>>& C, DataSet<T>& query_set) {
    
    std::vector<Data<T>> R;
    std::set<size_t> usedIndices; 
    
    while (R.size() < k && usedIndices.size() < O.size()) {
        double minDistance = std::numeric_limits<double>::max();
        size_t bestIndex = 0;
        bool foundCandidate = false;
        
        for (size_t i = 0; i < O.size(); i++) {
            // Skip si ya usamos este índice
            if (usedIndices.find(i) != usedIndices.end()) {
                continue;
            }
            
            const auto& o_i = O.getData(i);
            bool isValid = true;
            
            // Si está en strong influence set entonces no es válido
            for (const auto& r : R) {
                if (influence(o_i, r) >= influence(r, q) && 
                    influence(o_i, r) >= influence(o_i, q)) {
                    isValid = false;
                    break;
                }
            }
            

            if (isValid) {
                double currentDistance = this->distance(q, o_i);
                //solo es candidato si es uno de los más cercanos
                if (currentDistance < minDistance) {
                    minDistance = currentDistance;
                    bestIndex = i;
                    foundCandidate = true;
                }
            }
        }
        

        if (foundCandidate) {
            R.push_back(O.getData(bestIndex));
            usedIndices.insert(bestIndex);
        } else {
            break;
        }
    }

    usedIndices.clear();
    // Crear clusters con elementos de R como medoids
    for (size_t i = 0; i < R.size(); i++) {
        C.emplace_back();
        C.back().setMedoid(R[i]);

        for (size_t j = 0; j < O.size(); j++) {
            // Skip si ya usamos este índice
            if (usedIndices.find(j) != usedIndices.end()) {
                continue;
            }

            // Si está en strong influence del medoid entonces lo añadimos al cluster
            if (influence(R[i], O.getData(j)) >= influence(R[i], q) &&
                influence(O.getData(j), R[i]) >= influence(O.getData(j), q)) {
                C.back().addData(O.getData(j));
                query_set.addData(O.getData(j));
                usedIndices.insert(j);
            }
        }
    }
    return R;
}