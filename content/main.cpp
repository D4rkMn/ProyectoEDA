#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>

#include "Algorithms/DFM/DFM.h"
#include "Algorithms/BRID/BRID.h"
#include "Algorithms/MMR/MMR.h"
#include "Algorithms/Motley/Motley.h"
#include "Algorithms/Swap/Swap.h"
#include "DataStructures/Data/Data.h"
#include "DataStructures/DataSet/DataSet.h"
#include "DataStructures/Cluster/Cluster.h"

// Función para leer el archivo `query.txt`
bool readQueryFile(const std::string& filePath, std::string& algorithmType, std::vector<double>& queryEmbedding, std::string& queryContent) {
    std::ifstream queryFile(filePath);
    if (!queryFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo query.txt" << std::endl;
        return false;
    }

    std::getline(queryFile, algorithmType);
    std::string embeddingLine;
    std::getline(queryFile, embeddingLine);
    std::getline(queryFile, queryContent);

    queryEmbedding.clear();
    std::stringstream ss(embeddingLine);
    std::string value;
    while (std::getline(ss, value, ';')) {
        queryEmbedding.push_back(std::stod(value));
    }

    return true;
}

// Función principal
int main() {
    // Leer el archivo de datos y crear el dataset
    std::ifstream file("frontend/nombres_embeddings_yt.txt");
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo nombres_embeddings_yt.txt" << std::endl;
        return 1;
    }

    DataSet<std::string> dataset;
    std::string content, linea_numeros;
    std::vector<double> numeros;

    while (std::getline(file, content)) {
        numeros.clear();
        std::getline(file, linea_numeros);
        std::stringstream ss(linea_numeros);
        std::string numero;
        while (std::getline(ss, numero, ';')) {
            numeros.push_back(std::stod(numero));
        }
        dataset.addData(Data<std::string>(content, Point(numeros)));
    }

    // Leer el archivo query.txt
    std::string algorithmType, queryContent;
    std::vector<double> queryEmbedding;

    if (!readQueryFile("frontend/query.txt", algorithmType, queryEmbedding, queryContent)) {
        return 1;
    }

    std::cout << "Iniciando query:\n";

    Data<std::string> query(queryContent, Point(queryEmbedding));

    // Seleccionar y ejecutar el algoritmo

    // Distancia euclideana
    auto fn1 = [](const Data<std::string>& a, const Data<std::string>& b) {
        return static_cast<double>(a.getEmbedding().euclideanDistance(b.getEmbedding()));
    };
    // Similitud coseno
    auto fn2 = [](const Data<std::string>& a, const Data<std::string>& b) {
        return static_cast<double>(a.getEmbedding().cosineSimilarity(b.getEmbedding()));
    };
    // Distancia coseno
    auto fn3 = [](const Data<std::string>& a, const Data<std::string>& b) {
        return 1.0 - static_cast<double>(a.getEmbedding().cosineSimilarity(b.getEmbedding()));
    };

    std::vector<Cluster<std::string>> clusters;
    std::vector<Data<std::string>> result;

    if (algorithmType == "Motley") {
        Motley<std::string> motley(fn3, fn3, 0.3);
        result = motley.execute(10, query, dataset, clusters);
    } else if (algorithmType == "BRID") {
        BRID<std::string> brid(fn3, fn3);
        result = brid.execute(10, query, dataset, clusters);
    } else if (algorithmType == "Swap") {
        Swap<std::string> swap(fn2, fn3, 0.25);
        result = swap.execute(10, query, dataset, clusters);
    } else if (algorithmType == "MMR") {
        MMR<std::string> mmr(fn2, fn3, 0.25);
        result = mmr.execute(10, query, dataset, clusters);
    } else {
        std::cerr << "Error: Algoritmo desconocido: " << algorithmType << std::endl;
        return 1;
    }

    // Mostrar resultados en la consola
    std::cout << "Resultados para la consulta: " << queryContent << std::endl;
    for (const auto& data : result) {
        std::cout << data.getContent() << std::endl;
    }

    return 0;
}
