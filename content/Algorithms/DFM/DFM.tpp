#include <cmath>
#include <limits>

template<typename T>
void DFM<T>::initialize(std::vector<Data<T>>& R, DataSet<T>& O, 
                        std::vector<Cluster<T>>& C) {
    this->R = R;
    this->O = O;
    this->C = C;
}

template<typename T>
std::vector<float> DFM<T>::execute() {
    // TODO: Implementar el algoritmo principal DFM
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
float DFM<T>::execute_dunn_star() {
    // TODO: Implementar el índice Dunn*
    return 0.0f;
}

template<typename T>
float DFM<T>::execute_db_star() {
    // TODO: Implementar el índice Davies-Bouldin*
    return 0.0f;
}

template<typename T>
float DFM<T>::execute_sil_star() {
    //Calculo de los medoides mas cercanos
    std::vector<Data<T>> NearestMedoid;
    for(int i=0; i<C.size(); i++){
        float min_distance = std::numeric_limits<float>::max();
        int nearest_medoid_index = -1;
        for(int j=0; j<C.size(); j++){
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
    float SumatoriaFinal = 0;
    float resultParcial;
    for(int i = 0; i<C.size();i++){
        float resultParcial = 0;
        float resNum = 0;
        float resDen = 0;
        for(int j=0; j<C[i].size(); j++){
            resNum += distance_div(C[i].getData(j), NearestMedoid[i]);
        }
        for(int j=0; j<C[i].size(); j++){
            resDen += distance_div(C[i].getData(j), C[i].getMedoid());
        }
        resultParcial = (resNum*C[i].size())/resDen;
        SumatoriaFinal += resultParcial;
    }
    return SumatoriaFinal/C.size();
}

template<typename T>
float DFM<T>::execute_sigma_sim() {
    // TODO: Implementar la medida sigma de similitud
    return 0.0f;
}

template<typename T>
float DFM<T>::execute_sigma_div() {
    // TODO: Implementar la medida sigma de diversidad
    return 0.0f;
}

template<typename T>
float DFM<T>::execute_u_sim() {
    // TODO: Implementar la medida U de similitud
    return 0.0f;
}

template<typename T>
float DFM<T>::execute_u_div() {
    // TODO: Implementar la medida U de diversidad
    return 0.0f;
}