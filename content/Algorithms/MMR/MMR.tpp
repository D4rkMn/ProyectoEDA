#include "Algorithms/MMR/MMR.h"
#include <limits>

template<typename T>
double MMR<T>::objective_function(const Data<T>& o_i, const Data<T>& o_q, std::vector<Data<T>>& R) const {
    double result = (1 - lambda) * this->distance_sim(o_i, o_q);
    double sum = 0;
    for (const auto& o_j: R) {
        sum += this->distance_div(o_i, o_j);
    }
    result += 2 * lambda * sum;
    return result;
}

template<typename T>
std::vector<Data<T>> MMR<T>::execute(size_t k, const Data<T>& o_q, DataSet<T>& O, std::vector<Cluster<T>>& C) {
    std::vector<Data<T>> R;
    for (size_t i = 0; i < k; i++) {
        double max_score = std::numeric_limits<double>::min();
        const Data<T>* max_data = nullptr;
        for (const auto& o_i: O.getAllData()) {
            double current_score = objective_function(o_i, o_q, R);
            if (current_score > max_score) {
                max_score = current_score;
                max_data = &o_i;
            }
        }
        if (max_data) R.push_back(*max_data);
        else break;
    }
    return R;
}