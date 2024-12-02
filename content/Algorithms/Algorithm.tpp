#include "Algorithms/Algorithm.h"

template<typename T>
DataSet<T> NoveltyAlgorithm<T>::calculate_query_set(DataSet<T>& O, const Data<T>& query) {
    DataSet<T> O_prime;
    size_t sample_size = static_cast<size_t>(std::sqrt(O.getAllData().size()));
    std::vector<Data<T>> temp = O.getAllData();
    std::sort(temp.begin(), temp.end(), [query, this](const Data<T>& s1, const Data<T>& s2) -> bool {
        double d1 = this->distance_div(query, s1);
        double d2 = this->distance_div(query, s2);
        return d1 < d2;
    });
    for (size_t i = 0; i < sample_size; i++) {
        O_prime.addData(temp[i]);
    }
    return O_prime;
}