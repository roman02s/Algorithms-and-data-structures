#ifndef ALGORITHMS_SETGRAPH_H
#define ALGORITHMS_SETGRAPH_H

#include <iostream>
#include <vector>
#include <unordered_set>

#include "IGraph.h"

class SetGraph : public IGraph {
public:
    explicit SetGraph(int size);
    explicit SetGraph(const IGraph &graph);
    ~SetGraph() = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;
private:
    std::vector<std::unordered_set<int>> hastTable;
};

#endif //ALGORITHMS_SETGRAPH_H
