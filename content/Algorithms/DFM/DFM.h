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
    std::vector<float> answer;
    std::function<float(const Data<T>&, const Data<T>&)> distance_sim;
    std::function<float(const Data<T>&, const Data<T>&)> distance_div; 

public:
    DFM(std::function<float(const Data<T>&, const Data<T>&)> sim,
        std::function<float(const Data<T>&, const Data<T>&)> div){
        distance_sim = sim;
        distance_div = div;
        }

    void initialize(std::vector<Data<T>>& R, DataSet<T>& O, 
                   std::vector<Cluster<T>>& C);
    std::vector<float> execute();

    float execute_dunn_star();
    float execute_db_star();
    float execute_sil_star();
    float execute_sigma_sim();
    float execute_sigma_div();
    float execute_u_sim();
    float execute_u_div();
};

#include "Algorithms/DFM/DFM.tpp"

#endif