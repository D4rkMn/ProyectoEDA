#ifndef DAVIES_BOULDIN_STAR_H
#define DAVIES_BOULDIN_STAR_H

#include "../DataStructures/Cluster/Cluster.h"
#include <vector>
#include <functional>
#include <algorithm>

template<typename T>
class DaviesBouldinStar {
private:
    std::function<double(const Data<T>&, const Data<T>&)> div_distance;

    double calculateDiameter(const Cluster<T>& cluster) const {
        double max_div = 0.0;
        const auto& data = cluster.getAllData();
        
        for (size_t i = 0; i < data.size(); i++) {
            for (size_t j = i + 1; j < data.size(); j++) {
                double current_div = div_distance(data[i], data[j]);
                max_div = std::max(max_div, current_div);
            }
        }
        return max_div;
    }

public:
    DaviesBouldinStar(std::function<double(const Data<T>&, const Data<T>&)> div) 
        : div_distance(div) {}

    double calculate(const std::vector<Data<T>>& R, 
                    const std::vector<Cluster<T>>& C) const {
        if (C.empty()) return 0.0;

        double sum = 0.0;
        
        // Σ max((diam(Ci) + diam(Cj))/δdiv(oci,ocj))
        for (size_t i = 0; i < C.size(); i++) {
            double max_ratio = 0.0;
            
            for (size_t j = 0; j < C.size(); j++) {
                if (i == j) continue;
                
                double diam_i = calculateDiameter(C[i]);
                double diam_j = calculateDiameter(C[j]);
                
                double div_medoids = div_distance(C[i].getMedoid(), C[j].getMedoid());
                
                if (div_medoids > 0) {
                    double ratio = (diam_i + diam_j) / div_medoids;
                    max_ratio = std::max(max_ratio, ratio);
                }
            }
            
            sum += max_ratio;
        }
        
        // DB*(R,O',C) = (1/|C|) * sum
        return sum / static_cast<double>(C.size());
    }
};

#endif 