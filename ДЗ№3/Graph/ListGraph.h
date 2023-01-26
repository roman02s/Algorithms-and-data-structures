#ifndef ALGORITHMS_LISTGRAPH_H
#define ALGORITHMS_LISTGRAPH_H

#include <iostream>
#include <vector>

#include "IGraph.h"

class ListGraph: public IGraph {
public:
    explicit ListGraph(int size);
    explicit ListGraph(const IGraph &graph);
    ~ListGraph() = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;
private:
    std::vector<std::vector<int>> graph;
};


#endif //ALGORITHMS_LISTGRAPH_H
