#ifndef DB_H
#define DB_H

#include "Metric/Metric.h"

template<typename T>
class DB : public Metric<T> {
public:
    DB(std::function<float(const T&, const T&)> sim,
             std::function<float(const T&, const T&)> div)
        : Metric<T>(sim, div){}

    float execute(std::vector<T>& R, DataSet<T>& O,
                                 std::vector<Cluster<T>>& C) override;
};

#endif