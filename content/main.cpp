#include <iostream>
#include "Algorithms/DFM/DFM.h"
#include "Algorithms/BRID/BRID.h"
#include "Algorithms/MMR/MMR.h"
#include "Algorithms/Motley/Motley.h"
#include "Algorithms/Swap/Swap.h"
#include "DataStructures/Data/Data.h"
#include "DataStructures/DataSet/DataSet.h"
#include "DataStructures/Cluster/Cluster.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>

// Main de pruebas. puede ser descartado
int main() {
    
    auto fn1 = [](const Data<std::string>& a, const Data<std::string>& b) {
        return static_cast<double>( a.getEmbedding().euclideanDistance(b.getEmbedding()) );
    };

    //leer el archivo de datos y crear el dataset
    std::ifstream file("frontend/nombres_yt.txt");

    if(!file.is_open()){
        std::cout << "Error al abrir el archivo" << std::endl;
        return 1;
    }

    DataSet<std::string> dataset;

    std::string content;
    std::string linea_numeros;
    std::vector<double> numeros;

    while(std::getline(file, content)){
        numeros.clear();
        std::getline(file, linea_numeros);
        std::stringstream ss(linea_numeros);
        std::string numero;
        while (std::getline(ss, numero, ';')) {
            numeros.push_back(std::stod(numero)); // Convertir de string a int
        }
        dataset.addData(Data<std::string>(content, Point(numeros)));
    }

    auto data = dataset.getData(3);
    std::cout << data.getContent() << std::endl;

    // crear la consulta
    std::string query_Point;
    std::cout<<"Ingrese la consulta:"<<std::endl;
    std::cin>>query_Point;

    std::cout<<"Ingrese la consulta:"<<std::endl;
    //query Point tiene la forma: num1;num2;num3;...;numN
    std::stringstream ss(query_Point);
    std::string numero;
    numeros.clear();
    while (std::getline(ss, numero, ';')) {
        numeros.push_back(std::stod(numero)); // Convertir de string a int
    }

    Data<std::string> query("query", Point(numeros));

    //Probar con Motley

    Motley<std::string> motley(fn1, fn1, 0.5);
    std::vector<Cluster<std::string>> clusters;

    std::cout<<"Resultados con Motley:"<<std::endl;
    
    auto result = motley.execute(10, query, dataset, clusters);
    for (const auto& data : result) {
        std::cout << data.getContent() << std::endl;
    }

    //Probar con BRID
    BRID<std::string> brid(fn1, fn1);
    std::vector<Cluster<std::string>> clusters2;

    std::cout<<"Resultados con BRID:"<<std::endl;
    auto result2 = brid.execute(3, query, dataset, clusters2);
    for (const auto& data : result2) {
        std::cout << data.getContent() << std::endl;
    }
    
    return 0;
}