#ifndef ALGORITHMS_MATRIXGRAPH_H
#define ALGORITHMS_MATRIXGRAPH_H

#include <iostream>
#include <vector>

#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int size);
    explicit MatrixGraph(const IGraph &graph);
    ~MatrixGraph() = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;
private:
    std::vector<std::vector<bool>> graph;
};

#endif //ALGORITHMS_MATRIXGRAPH_H
