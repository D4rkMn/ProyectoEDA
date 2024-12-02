/* #include "Metrics/DaviesBouldinStar.h"
#include <iostream>

int main() {
    auto div_distance = [](const Data<double>& a, const Data<double>& b) {
        return a.getEmbedding().euclideanDistance(b.getEmbedding());
    };

    DaviesBouldinStar<double> dbs(div_distance);

    std::vector<double> coords1 = {0.0, 0.0};
    std::vector<double> coords2 = {1.0, 1.0};
    std::vector<double> coords3 = {5.0, 5.0};
    std::vector<double> coords4 = {6.0, 6.0};

    Data<double> d1(1.0, Point(coords1));
    Data<double> d2(2.0, Point(coords2));
    Data<double> d3(3.0, Point(coords3));
    Data<double> d4(4.0, Point(coords4));

    Cluster<double> c1;
    c1.setMedoid(d1);
    c1.addData(d1);
    c1.addData(d2);

    Cluster<double> c2;
    c2.setMedoid(d3);
    c2.addData(d3);
    c2.addData(d4);

    std::vector<Cluster<double>> clusters = {c1, c2};

    std::vector<Data<double>> R = {d1, d3};

    double db_star = dbs.calculate(R, clusters);

    std::cout << "Davies-Bouldin Star Index: " << db_star << std::endl;

    // Verificación manual:
    std::cout << "\nVerificación paso a paso:" << std::endl;
    
    std::cout << "Diámetro cluster 1: " << div_distance(d1, d2) << std::endl;
    std::cout << "Diámetro cluster 2: " << div_distance(d3, d4) << std::endl;
    std::cout << "Distancia entre medoides: " << div_distance(d1, d3) << std::endl;

    return 0;
} */