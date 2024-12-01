#include "Algorithms/Motley/Motley.h"

template<typename T>
std::vector<Data<T>> Motley<T>::execute(size_t k, const Data<T>& q, DataSet<T>& O, std::vector<Cluster<T>>& C) {
    auto content = O.getAllData();
    //ordenar por similutud con q
    std::sort(content.begin(), content.end(), [&q, this](const Data<T>& a, const Data<T>& b) -> bool {
        return this->distance_sim(a, q) < this->distance_sim(b, q);
    });

    //inicializar conjunto Resultado
    std::vector<Data<T>> R;
    R.push_back(content[0]);

    bool is_far;
    for(size_t i=1; i<content.size(); i++){
        is_far = true;
        for(size_t j=0; j<R.size(); j++){
            if(this->distance_sim(R[j], content[i]) < r){
                is_far = false;
                break;
            }
        }
        if(is_far){
            R.push_back(content[i]);
        }

        if(R.size() == k){
            break;
        }  
    }

    C.clear();

    //modificar los clusters, hacieno que cada elemento de R sea el medoid de su cluster
    for(size_t i=0; i<R.size(); i++){
        Cluster<T> cluster;
        cluster.setMedoid(R[i]);
        C.push_back(cluster);
    }

    //asignar cada elemento de O al cluster cuyo medoid sea el más cercano, usar distancia de similitud
    bool flag;
    for(size_t i=0; i<O.size(); i++){
        double min_distance = std::numeric_limits<double>::max();
        int cluster_index = -1;
        flag = false;
        for(size_t j=0; j<C.size(); j++){

            if (O.getData(i) == C[j].getMedoid()){
                flag = true;
                cluster_index = j;
                break;
            }
            if(this->distance_sim(O.getData(i), C[j].getMedoid()) < min_distance){
                min_distance = this->distance_sim(O.getData(i), C[j].getMedoid());
                cluster_index = j;
            }
        }
        if(flag){
            continue;
        }
        C[cluster_index].addData(O.getData(i));
    }
    return R;
}