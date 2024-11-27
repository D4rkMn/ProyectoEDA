#ifndef DFM_H
#define DFM_H

#include "Metric/Metric.h"
#include "Metric/Sil/Sil.h"
#include "Metric/Dunn/Dunn.h"
#include "Metric/DB/DB.h"
#include <vector>

// TODO: en teoria DFM no retorna float como output de execute, sino una tupla 7-dimensional? revisar eso.
template<typename T>
class DFM : public Metric<T> {
private:
    std::vector<float> answer;
    Sil<T> sil;
    Dunn<T> dunn;
    DB<T> db;

public:
    DFM(std::function<float(const T&, const T&)> sim,
        std::function<float(const T&, const T&)> div);
    
    void initialize(std::vector<T>& R, DataSet<T>& O, 
                   std::vector<Cluster<T>>& C);
                   
    float execute(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C) override;

    float execute_dunn_star(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C);
    float execute_db_star(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C);
    float execute_sil_star(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C);
    float execute_sigma_sim(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C);
    float execute_sigma_div(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C);
    float execute_u_sim(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C);
    float execute_u_div(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C);
};

#include "Metric/DFM/DFM.tpp"

#endif