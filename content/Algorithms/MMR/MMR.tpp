#include "Algorithms/MMR/MMR.h"
#include <limits>

template<typename T>
float MMR<T>::objective_function(const T& o_i, const T& o_q, std::vector<T>& R) const {
    float result = (1 - lambda) * distance_sim(o_i, o_q);
    float sum = 0;
    for (const auto& o_j: R) {
        sum += distance_div(o_i, o_j);
    }
    result += 2 * lambda * sum;
    return result;
}

template<typename T>
std::vector<T> MMR<T>::execute(size_t k, const T& o_q, DataSet<T>& O, std::vector<Cluster<T>>& C) {
    std::vector<T> R;
    for (size_t i = 0; i < k; i++) {
        float max_score = std::numeric_limits<float>::min();
        T* max_data = nullptr;
        for (const auto& o_i: O) {
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