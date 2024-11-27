#include "Algorithms/MMR/MMR.h"
#include <limits>

template<typename T>
float MMR<T>::objective_function(Data<T>& o_i, Data<T>& o_q, std::vector<Data<T>>& R) const {
    float result = (1 - lambda) * distance_sim(o_i, o_q);
    float sum = 0;
    for (const auto& o_j: R) {
        sum += distance_div(o_i, o_j);
    }
    result += 2 * lambda * sum;
    return result;
}

template<typename T>
std::vector<Data<T>> MMR<T>::execute(size_t k, Data<T>& o_q, DataSet<T>& O, std::vector<Cluster<T>>& C) {
    std::vector<Data<T>> R;
    for (size_t i = 0; i < k; i++) {
        float max_score = std::numeric_limits<float>::min();
        Data<T>* max_data = nullptr;
        for (const auto& o_i: O.getAllData()) {
            float current_score = objective_function(o_i, o_q, R);
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