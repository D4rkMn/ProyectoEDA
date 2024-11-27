#include "Algorithms/Swap/Swap.h"
#include <unordered_set>
#include <algorithm>
#include <queue>

// Swap con MMR
template<typename T>
float Swap<T>::objective_function(Data<T>& o_i, Data<T>& o_q, std::vector<Data<T>>& R) const {
    float result = (1 - lambda) * distance_sim(o_i, o_q);
    float sum = 0;
    for (const auto& o_j: R) {
        sum += distance_div(o_i, o_j);
    }
    result += 2 * lambda * sum;
    return result;
}

template<typename T>
std::vector<Data<T>> Swap<T>::kNN(size_t k, Data<T>& o_q, DataSet<T>& O) const {
    std::priority_queue< std::pair<float, Data<T>*> > R;
    float inf = std::numeric_limits<float>::max();
    for (size_t i = 0; i < k; i++) {
        R.push({inf, nullptr});
    }
    for (const auto& o_i: O.getAllData()) {
        float current_distance = distance_sim(o_i, o_q);
        float max_distance = R.top().first;
        if (max_distance > current_distance) {
            R.push({current_distance, &o_i});
            R.pop();
        }
    }
    std::vector<Data<T>> result; result.reserve(k);
    while (!R.empty()) {
        if (!R.top().second) break;
        result.push_back( *(R.top().second) );
        R.pop();
    }
    return result;
}

template<typename T>
std::vector<Data<T>> Swap<T>::execute(size_t k, Data<T>& o_q, DataSet<T>& O, std::vector<Cluster<T>>& C) {
    std::vector<Data<T>> R = kNN(k, o_q, O);
    // get O minus R
    std::vector<Data<T>> O_minus_R;
    std::set_difference(
        O.getAllData().begin(), O.getAllData().end(), R.begin(), R.end(), std::back_inserter(O_minus_R)
    );
    sort(O_minus_R.begin(), O_minus_R.end(), [this, o_q](const Data<T>& a, const Data<T>& b) {
        float d1 = distance_sim(o_q, a);
        float d2 = distance_sim(o_q, b);
        return d1 < d2;
    });

    // Swap procedure
    std::unordered_set<size_t> swapped;
    for (size_t i = 0; i < O_minus_R.size(); i++) {
        
        // if every element has already been swapped, end
        if (swapped.size() == R.size()) break;

        for (size_t j = 0; j < R.size(); j++) {
            // if element already swapped, skip
            if (swapped.find(j) != swapped.end()) continue;

            float prev_score = objective_function(R[j], o_q, R);
            // test swap
            std::swap(O_minus_R[i], R[j]);
            float new_score = objective_function(R[j], o_q, R);

            // if score is better, change is permanent
            if (new_score > prev_score) {
                swapped.insert(j);
                break;
            }
            // else, undo swap
            else {
                std::swap(O_minus_R[i], R[j]);
            }
        }
    }
    return R;
}