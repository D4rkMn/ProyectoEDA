#include "Algorithms/MMR/MMR.h"
#include <unordered_set>
#include <iostream>
#include <limits>

template<typename T>
double MMR<T>::objective_function(const Data<T>& o_i, const Data<T>& o_q, std::vector<Data<T>>& R) const {
    double result = (1 - this->lambda) * this->distance_sim(o_i, o_q);
    double sum = 0;
    for (const auto& o_j: R) {
        sum += this->distance_div(o_i, o_j);
    }
    result += this->lambda * sum;
    return result;
}

template<typename T>
std::vector<Data<T>> MMR<T>::execute(size_t k, const Data<T>& o_q, DataSet<T>& O, std::vector<Cluster<T>>& C) {
    std::vector<Data<T>> R;

    std::unordered_set<size_t> taken;
    for (size_t i = 0; i < k; i++) {
        double max_score = std::numeric_limits<double>::min();
        size_t index = 0;
        for (size_t j = 0; j < O.getAllData().size(); j++) {
            // if element already taken, skip
            if (taken.find(j) != taken.end()) continue;

            const Data<T>& o_i = O.getData(j);
            double current_score = objective_function(o_i, o_q, R);
            if (current_score > max_score) {
                max_score = current_score;
                index = j;
            }
        }
        R.push_back(O.getData(index));
        taken.insert(index);
    }

    // create clusters with elements from R as medoids
    for (size_t i = 0; i < R.size(); i++) {
        C.emplace_back();
        C.back().setMedoid(R[i]);
    }

    // for each element in O', assign to a medoid
    for (size_t i = 0; i < O.getAllData().size(); i++) {
        double min_distance = std::numeric_limits<double>::max();
        size_t index = 0;
        for (size_t j = 0; j < R.size(); j++) {
            double current_distance = this->distance_div(R[j], O.getAllData()[i]);
            if (min_distance > current_distance) {
                min_distance = current_distance;
                index = j;
            }
        }
        C[index].addData(O.getAllData()[i]);
    }
    return R;
}