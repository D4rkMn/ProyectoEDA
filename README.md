# Métricas de calidad para algoritmos de Clustering y Diversidad

## Descripción del Proyecto
Este proyecto implementa una métrica para la clasificación de resultados de búsquedas de similaridad diversificadas llamada DFM (Diversity Features Model). Adicionalmente, se implementa una suite de algoritmos de clustering y diversidad, incluyendo Motley, BRID, Swap y MMR. El sistema está diseñado para manejar diversos tipos de datos a través del uso de templates en C++, permitiendo una gran flexibilidad en su aplicación.

## Integrantes del Equipo
- Melisa Rivera
- Cesar Perales
- Alejandro Oré
- Alexandra Shulca

## Estructura del Proyecto
```
.
├── content/
│   ├── Point.h
│   ├── Data.h
│   ├── DataSet.h
│   ├── Cluster.h
│   ├── Algorithm.h
│   ├── DFM.h
│   ├── Motley.h
│   ├── BRID.h
│   ├── Swap.h
│   └── MMR.h
│   ├── Point.cpp
│   ├── Data.cpp
│   ├── DataSet.cpp
│   ├── Cluster.cpp
│   └── Algorithm.cpp
├── README.md
└── .gitignore
```

## Características Principales
- Implementación genérica usando templates de C++
- Múltiples algoritmos de clustering y diversidad
- Métricas de evaluación incorporadas
- Soporte para diferentes tipos de datos
- Arquitectura extensible para nuevos algoritmos

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
- Funciones de distancia configurables
- Interface común para ejecución

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
- C++17 o superior
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
- [ ] Implementar validación de parámetros en todos los algoritmos
- [ ] Agregar tests unitarios
- [ ] Optimizar rendimiento de operaciones críticas
- [ ] Documentar casos de uso específicos
- [ ] Agregar ejemplos de implementación
- [ ] Agregar visualización de resultados
