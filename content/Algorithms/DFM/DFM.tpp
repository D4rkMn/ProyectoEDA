#include <cmath>
#include <limits>

#include "Algorithms/DFM/DFM.h"
#include "Metrics/DiversityMetrics.h"
#include "Metrics/DaviesBouldinStar.h"

template<typename T>
void DFM<T>::initialize(std::vector<Data<T>>& R, DataSet<T>& O, 
                        std::vector<Cluster<T>>& C, Data<T>& query) {
    this->R = R;
    this->O = O;
    this->C = C;
    this->query = query;
}

template<typename T>
std::vector<double> DFM<T>::execute() {
    answer[0] = execute_dunn_star();
    answer[1] = execute_db_star();
    answer[2] = execute_sil_star();
    answer[3] = execute_sigma_sim();
    answer[4] = execute_sigma_div();
    answer[5] = execute_u_sim();
    answer[6] = execute_u_div();

    return answer;
}

template<typename T>
double DFM<T>::execute_dunn_star() {
    //calcular el max C_m pertenece a C (max o_h pertenece a C_m(distance_div(o_h, query)))
    double max_intracluster_distance = 0.0f;

    for (size_t m = 0; m < C.size(); m++) {
        double intracluster_distance = 0.0f;

        auto data_m = C[m].getAllData();
        for (size_t h = 0; h < data_m.size(); h++) {
            intracluster_distance += distance_div(data_m[h], query);
        }

        if (intracluster_distance > max_intracluster_distance) {
            max_intracluster_distance = intracluster_distance;
        }
    }

    if (max_intracluster_distance == 0.0f) {
        return 0.0f;
    }

    //recorrer todos los pares de clusters en la lista de clusters
    double min_intercluster_normalization = std::numeric_limits<double>::max();

    for(size_t i=0; i<C.size(); i++){
        for(size_t j=0; j<C.size(); j++){
            if(i != j){
                //calcular distancia entre medoides o_i y o_j
                double intercluster_distance = distance_div(C[i].getMedoid(), C[j].getMedoid());

                //calcular la normalización
                double normalization = intercluster_distance / max_intracluster_distance;

                if (normalization < min_intercluster_normalization) {
                    min_intercluster_normalization = normalization;
                }
            }
        }
    }

    return min_intercluster_normalization;
}

template<typename T>
double DFM<T>::execute_db_star() {
    DaviesBouldinStar<T> db(distance_div);
    return db.calculate(R, C);
}

template<typename T>
double DFM<T>::execute_sil_star() {
    //Calculo de los medoides mas cercanos
    std::vector<Data<T>> NearestMedoid;
    for(size_t i=0; i<C.size(); i++){
        double min_distance = std::numeric_limits<double>::max();
        int nearest_medoid_index = -1;
        for(size_t j=0; j<C.size(); j++){
            if(i != j){
                if(distance_sim(C[i].getMedoid(), C[j].getMedoid()) < min_distance){
                    min_distance = distance_sim(C[i].getMedoid(), C[j].getMedoid());
                    nearest_medoid_index = j;
                }
            }
        }
        NearestMedoid.push_back(C[nearest_medoid_index].getMedoid());
    }

    //Calculo de los coeficientes de silueta
    double SumatoriaFinal = 0;
    for(size_t i = 0; i<C.size();i++){
        double resultParcial = 0;
        double resNum = 0;
        double resDen = 0;
        for(size_t j=0; j<C[i].size(); j++){
            resNum += distance_div(C[i].getData(j), NearestMedoid[i]);
        }
        for(size_t j=0; j<C[i].size(); j++){
            resDen += distance_div(C[i].getData(j), C[i].getMedoid());
        }
        if (resDen != 0) {
            resultParcial = (resNum)/(resDen*C[i].size());
        }
        SumatoriaFinal += resultParcial;
    }
    return SumatoriaFinal/C.size();
}

template<typename T>
double DFM<T>::execute_sigma_sim() {
    DiversityMetrics<T> dm(distance_div, distance_sim);
    auto r = dm.calculate(R);
    return r.o_sim;
}

template<typename T>
double DFM<T>::execute_sigma_div() {
    DiversityMetrics<T> dm(distance_div, distance_sim);
    auto r = dm.calculate(R);
    return r.o_div;
}

template<typename T>
double DFM<T>::execute_u_sim() {
    DiversityMetrics<T> dm(distance_div, distance_sim);
    auto r = dm.calculate(R);
    return r.u_sim;
}

template<typename T>
double DFM<T>::execute_u_div() {
    DiversityMetrics<T> dm(distance_div, distance_sim);
    auto r = dm.calculate(R);
    return r.u_div;
}