#include "Algorithms/MMR/MMR.h"
#include <iostream>
#include <limits>

template<typename T>
double MMR<T>::objective_function(const Data<T>& o_i, const Data<T>& o_q, std::vector<Data<T>>& R) const {
    double result = (1 - lambda) * this->distance_sim(o_i, o_q);
    double sum = 0;
    for (const auto& o_j: R) {
        sum += this->distance_div(o_i, o_j);
    }
    result += lambda * sum;
    return result;
}

template<typename T>
std::vector<Data<T>> MMR<T>::execute(size_t k, const Data<T>& o_q, DataSet<T>& O, std::vector<Cluster<T>>& C) {
    std::vector<Data<T>> R;
    std::vector<Data<T>> O_minus_R = O.getAllData();
    for (size_t i = 0; i < k; i++) {
        double max_score = std::numeric_limits<double>::min();
        size_t index = 0;
        for (size_t j = 0; j < O_minus_R.size(); j++) {
            const Data<T>& o_i = O_minus_R[j];
            double current_score = objective_function(o_i, o_q, R);
            if (current_score > max_score) {
                max_score = current_score;
                index = j;
            }
        }
        R.push_back(O_minus_R[index]);
        O_minus_R.erase(O_minus_R.begin() + index);
    }
    return R;
}