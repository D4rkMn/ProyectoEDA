#ifndef DFM_H
#define DFM_H

#include "Algorithm.h"
#include <vector>

template<typename T>
class DFM : public Algorithm<T> {
private:
    std::vector<float> answer;

public:
    DFM(std::function<float(const T&, const T&)> sim,
        std::function<float(const T&, const T&)> div);
    
    void initialize(std::vector<T>& R, DataSet<T>& O, 
                   std::vector<Cluster<T>>& C);
    std::vector<T> execute(DataSet<T>& O, 
                          std::vector<Cluster<T>>& C) override;
    
    float execute_dunn_star();
    float execute_db_star();
    float execute_sil_star();
    float execute_sigma_sim();
    float execute_sigma_div();
    float execute_u_sim();
    float execute_u_div();
};

#endif