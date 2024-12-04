#include "Visualization2D/WindowContent/WindowContent.h"
#include "Algorithms/DFM/DFM.h"
#include "Algorithms/BRID/BRID.h"
#include "Algorithms/MMR/MMR.h"
#include "Algorithms/Motley/Motley.h"
#include "Algorithms/Swap/Swap.h"
#include "DataStructures/Data/Data.h"
#include "DataStructures/DataSet/DataSet.h"
#include "DataStructures/Cluster/Cluster.h"

void ConcreteContent::resetQuery() {
    lines.clear();
    circles.clear();
    for (size_t i = 0; i < points.size(); i++) {
        points[i].color = SDL_Color{30, 33, 110, 255};
        points[i].isCircle = true;
    }
}

void ConcreteContent::processQuery(SDL_Renderer* renderer) {
    resetQuery();

    bool novelty = false;
    bool _motley = false;
    double motleyRad = 0;

    Data<CanvasPoint*> query(queryPoint, queryPoint->toPoint());
    DataSet<CanvasPoint*> dataset;

    for (size_t i = 0; i < points.size(); i++) {
        dataset.addData(Data<CanvasPoint*>(&points[i], points[i].toPoint()));
        points[i].isCircle = true;
    }

    const size_t query_size = 3;

    DataSet<CanvasPoint*> query_set;
    std::vector<Cluster<CanvasPoint*>> clusters;
    std::vector<Data<CanvasPoint*>> result;

    // Distancia euclideana
    auto fn1 = [](const Data<CanvasPoint*>& a, const Data<CanvasPoint*>& b) {
        return static_cast<double>(a.getEmbedding().euclideanDistance(b.getEmbedding()));
    };
    // Similitud coseno
    auto fn2 = [](const Data<CanvasPoint*>& a, const Data<CanvasPoint*>& b) {
        return static_cast<double>(a.getEmbedding().cosineSimilarity(b.getEmbedding()));
    };

    if (currentQuery == QueryType::MMR) {
        double lambda = 0.5;
        MMR<CanvasPoint*> mmr(fn2, fn1, lambda);
        query_set = mmr.calculate_query_set(dataset, query);
        result = mmr.execute(query_size, query, query_set, clusters);
        novelty = true;
    }

    if (currentQuery == QueryType::SWAP) {
        double lambda = 0.5;
        Swap<CanvasPoint*> swap(fn2, fn1, lambda);
        query_set = swap.calculate_query_set(dataset, query);
        result = swap.execute(query_size, query, query_set, clusters);
        novelty = true;
    }

    if (currentQuery == QueryType::MOTLEY) {
        double radius = motleyRad = 100;
        Motley<CanvasPoint*> motley(fn1, radius);
        result = motley.execute(query_size, query, dataset, clusters, query_set);
        _motley = true;
    }

    if (currentQuery == QueryType::BRID) {
        BRID<CanvasPoint*> brid(fn1);
        result = brid.execute(query_size, query, dataset, clusters, query_set);
    }

    for (size_t i = 0; i < points.size(); i++) {
        points[i].color = SDL_Color{212, 211, 209};
    }

    for (size_t i = 0; i < result.size(); i++) {
        CanvasPoint* p = result[i].getContent();
        lines.push_back({queryPoint->toPoint(), p->toPoint()});
        p->isCircle = false;
    }

    for (size_t i = 0; i < clusters.size(); i++) {
        for (size_t j = 0; j < clusters[i].size(); j++) {
            CanvasPoint* p = clusters[i].getData(j).getContent();
            if (i == 0) {
                p->color = SDL_Color{255,189,74};
            }
            if (i == 1) {
                p->color = SDL_Color{153,226,101};
            }
            if (i == 2) {
                p->color = SDL_Color{255,92,92};
            }
        }
    }

    if (novelty) {
        double maxRad = -1;
        for (size_t i = 0; i < query_set.size(); i++) {
            maxRad = std::max(maxRad, fn1(query, query_set.getData(i)));
        }
        circles.push_back({queryPoint->toPoint(), (int)maxRad + queryPoint->size});
    }
    else if (_motley) {
        for (size_t i = 0; i < clusters.size(); i++) {
            circles.push_back({clusters[i].getMedoid().getContent()->toPoint(), (int)motleyRad + clusters[i].getMedoid().getContent()->size});
        }
    }
    else {
        for (size_t i = 0; i < clusters.size(); i++) {
            double maxRad = -1;
            auto medoid = clusters[i].getMedoid();
            for (size_t j = 0; j < clusters[i].size(); j++) {
                auto p = clusters[i].getData(j);
                maxRad = std::max(maxRad, fn1(medoid, p));
            }
            circles.push_back({medoid.getContent()->toPoint(), (int)maxRad + medoid.getContent()->size});
        }
    }

}