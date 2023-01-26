#ifndef ALGORITHMS_ARCGRAPH_H
#define ALGORITHMS_ARCGRAPH_H

#include <iostream>
#include <vector>

#include "IGraph.h"

class ArcGraph: public IGraph {
public:
    explicit ArcGraph(int size);
    explicit ArcGraph(const IGraph &graph);
    ~ArcGraph() = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;
private:
    std::vector<std::pair<int, int>> pairs;
    int count;
};


#endif //ALGORITHMS_ARCGRAPH_H
