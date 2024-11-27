#ifndef DFM_H
#define DFM_H

#include "DataStructures/DataSet/DataSet.h"
#include "DataStructures/Cluster/Cluster.h"
#include "DataStructures/Data/Data.h"
#include <functional>
#include <vector>

template<typename T>
class DFM {
private:
    std::vector<double> answer;
    std::function<double(const Data<T>&, const Data<T>&)> distance_sim;
    std::function<double(const Data<T>&, const Data<T>&)> distance_div;
    std::vector<Data<T>> R;
    DataSet<T> O;
    std::vector<Cluster<T>> C;

public:
    DFM(std::function<double(const Data<T>&, const Data<T>&)> sim,
        std::function<double(const Data<T>&, const Data<T>&)> div) {
        distance_sim = sim;
        distance_div = div;
        answer.reserve(7);
        }

    void initialize(std::vector<Data<T>>& R, DataSet<T>& O, 
                   std::vector<Cluster<T>>& C);
    std::vector<double> execute();

    double execute_dunn_star();
    double execute_db_star();
    double execute_sil_star();
    double execute_sigma_sim();
    double execute_sigma_div();
    double execute_u_sim();
    double execute_u_div();
};

#include "Algorithms/DFM/DFM.tpp"

#endif