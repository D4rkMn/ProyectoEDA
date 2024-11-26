#ifndef DFM_H
#define DFM_H

#include "Algorithms/Algorithm.h"
#include <vector>

template<typename T>
class DFM : public Algorithm<T> {
private:
    std::vector<float> answer;

public:
    DFM(std::function<float(const Data<T>&, const Data<T>&)> sim,
        std::function<float(const Data<T>&, const Data<T>&)> div)
        : Algorithm<T>(sim, div) {}
    
    void initialize(std::vector<T>& R, DataSet<T>& O, 
                   std::vector<Cluster<T>>& C);
    void initialize(std::vector<Data<T>>& R, DataSet<T>& O, 
                   std::vector<Cluster<T>>& C);
    std::vector<T> execute();
    
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