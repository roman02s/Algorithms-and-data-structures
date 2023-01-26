#include "ArcGraph.h"


ArcGraph::ArcGraph(int size) : pairs(size), count(0) {}

void ArcGraph::AddEdge(int from, int to) {
    pairs.emplace_back(from, to);
    count++;
}

int ArcGraph::VerticesCount() const {
    return count;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;
    for (const auto & pair : pairs) {
        if (pair.first == vertex) {
            next.push_back(pair.second);
        }
    }
    return next;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (auto p : pairs) {
        if (p.second == vertex) {
            prev.push_back(p.first);
        }
    }
    return prev;
}

ArcGraph::ArcGraph(const IGraph &graph) : pairs(graph.VerticesCount()), count(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        auto next = graph.GetNextVertices(i);
        for (auto j : next) {
            pairs.emplace_back(i, j);
        }
    }
}


