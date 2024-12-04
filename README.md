# Métricas de calidad para algoritmos de Clustering y Diversidad

## Descripción del Proyecto
Este proyecto implementa una métrica para la clasificación de resultados de búsquedas de similaridad diversificadas llamada DFM (Diversity Features Model). Adicionalmente, se implementa una suite de algoritmos de clustering y diversidad, incluyendo Motley, BRID, Swap y MMR. El sistema está diseñado para manejar diversos tipos de datos a través del uso de templates en C++, permitiendo una gran flexibilidad en su aplicación.

## Integrantes del Equipo
- Melisa Rivera
- Cesar Perales
- Alejandro Ore
- Alexandra Shulca

## Estructura del Proyecto
```
.
├── content
│   ├── Algorithms
│   │   ├── Algorithm.h
│   │   ├── Algorithm.tpp
│   │   ├── BRID
│   │   │   ├── BRID.h
│   │   │   └── BRID.tpp
│   │   ├── DFM
│   │   │   ├── DFM.h
│   │   │   └── DFM.tpp
│   │   ├── MMR
│   │   │   ├── MMR.h
│   │   │   └── MMR.tpp
│   │   ├── Motley
│   │   │   ├── Motley.h
│   │   │   └── Motley.tpp
│   │   └── Swap
│   │       ├── Swap.h
│   │       └── Swap.tpp
│   ├── DataStructures
│   │   ├── Cluster
│   │   │   ├── Cluster.h
│   │   │   └── Cluster.tpp
│   │   ├── Data
│   │   │   └── Data.h
│   │   ├── DataSet
│   │   │   ├── DataSet.h
│   │   │   └── DataSet.tpp
│   │   └── Point
│   │       ├── Point.cpp
│   │       └── Point.h
│   ├── Metrics
│   │   ├── DaviesBouldinStar.h
│   │   └── DiversityMetrics.h
│   └── Visualization2D
│       ├── CanvasPoint
│       │   └── CanvasPoint.h
│       ├── WindowContent
│       │   ├── ProcessQuery.cpp
│       │   ├── WindowContent.cpp
│       │   └── WindowContent.h
│       └── WindowHandler
│           ├── Events.cpp
│           ├── WindowHandler.cpp
│           └── WindowHandler.h
├── frontend
│   ├── app.py
│   ├── csv_to_titles.py
│   ├── DFM
│   ├── generate.py
│   ├── index.html
│   ├── Last.fm_data.csv
│   └── nombres_yt.txt
├── DFM
├── main.cpp
├── Visualization
├── visuals.cpp
├── requeriments.txt
├── Makefile
├── README.md
├── .gitignore
```

## Características Principales
- Implementación genérica usando templates de C++
- Múltiples algoritmos de clustering y diversidad
- Métricas de evaluación incorporadas
- Soporte para diferentes tipos de datos
- Arquitectura extensible para nuevos algoritmos
- Dos tipos de visualizaciones (baja y alta dimensionalidad)

## Clases Principales

### Point
Representa un punto en un espacio n-dimensional.
- Coordenadas vectoriales
- Operaciones aritméticas básicas

### Data
Clase template para encapsular datos con su embedding.
- Contenido genérico
- Point como embedding

### DataSet
Colección de datos del mismo tipo.
- Operaciones de acceso
- Manipulación de conjuntos de datos

### Cluster
Representa un cluster de elementos.
- Medoide como representante
- Operaciones sobre elementos del cluster

### Algorithm
Clase base abstracta para todos los algoritmos.
- Interface común para ejecución

### NoveltyAlgorithm
Clase base abstracta para los algoritmos de novelty.
- Funciones de distancia de similitud y diversificación
- 'Lambda' para configurar la relevancia de cada parámetro

### CoverageAlgorithm
Clase base abstracta para los algoritmos de coverage.
- Funcion de distancia configurable

## Algoritmos Implementados

### DFM (Diversity Features Model)
- Inicialización de clusters
- Métricas de evaluación:
  - Dunn*
  - Davies-Bouldin*
  - Silhouette*
  - Sigma (similitud/diversidad)
  - U (similitud/diversidad)

### Motley
- Algoritmo basado en medoides
- Balance entre similitud y diversidad

### BRID
- Algoritmo de clustering bidireccional
- Optimización de distancias

### Swap
- Algoritmo de intercambio
- Optimización local

### MMR (Maximal Marginal Relevance)
- Selección iterativa
- Balance configurable entre relevancia y diversidad

## Requisitos del Sistema
- C++17 o superior (con SDL2 para compilar 'visuals')
- Python (instalar requirements.txt)
- Compilador compatible (GCC, Clang, MSVC)

## Uso Básico
```cpp
#include "DataStructures/DataSet/DataSet.h"
#include "Algorithms/DFM/DFM.h"

// Crear conjunto de datos
DataSet<YourDataType> dataset;
// Añadir datos...

// Configurar algoritmo
auto simFunction = [](const Data<YourDataType>& a, const Data<YourDataType>& b) -> double {
    // Implementar función de similitud
};
auto divFunction = [](const Data<YourDataType>& a, const Data<YourDataType>& b) -> double {
    // Implementar función de diversidad
};

DFM<YourDataType> dfm(simFunction, divFunction);
std::vector<Cluster<YourDataType>> clusters;

// Ejecutar algoritmo
dfm.initialize(result, dataset, clusters);
dfm.execute();
```


## TO-DOs
- [X] Documentar casos de uso específicos
- [X] Agregar ejemplos de implementación
- [X] Agregar visualización de resultados
