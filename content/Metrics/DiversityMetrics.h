#ifndef DIVERSITY_METRICS_H
#define DIVERSITY_METRICS_H

#include <vector>
#include <cmath>
#include <functional>
#include "DataStructures/Data/Data.h"

template<typename T>
class DiversityMetrics {
private:
    std::function<double(const Data<T>&, const Data<T>&)> div_distance;
    std::function<double(const Data<T>&, const Data<T>&)> sim_distance;

public:
    DiversityMetrics(std::function<double(const Data<T>&, const Data<T>&)> div,
                    std::function<double(const Data<T>&, const Data<T>&)> sim) 
        : div_distance(div), sim_distance(sim) {}

    struct MetricResults {
        double u_div;  // media de diversidad
        double o_div;  // desviación estándar de diversidad
        double u_sim;  // media de similitud
        double o_sim;  // desviación estándar de similitud
    };

    MetricResults calculate(const std::vector<Data<T>>& result) {
        MetricResults metrics{0.0, 0.0, 0.0, 0.0};
        
        if (result.size() < 2) return metrics;

        int n = 0;
        double sum_div = 0.0;
        double sum_sim = 0.0;

        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = i + 1; j < result.size(); j++) {
                sum_div += div_distance(result[i], result[j]);
                sum_sim += sim_distance(result[i], result[j]);
                n++;
            }
        }

        metrics.u_div = sum_div / n;
        metrics.u_sim = sum_sim / n;

        //  desviacion estándar
        double sum_squared_div = 0.0;
        double sum_squared_sim = 0.0;

        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = i + 1; j < result.size(); j++) {
                double div = div_distance(result[i], result[j]);
                double sim = sim_distance(result[i], result[j]);
                
                sum_squared_div += std::pow(div - metrics.u_div, 2);
                sum_squared_sim += std::pow(sim - metrics.u_sim, 2);
            }
        }

        metrics.o_div = std::sqrt(sum_squared_div / n);
        metrics.o_sim = std::sqrt(sum_squared_sim / n);

        return metrics;
    }
};

#endif 