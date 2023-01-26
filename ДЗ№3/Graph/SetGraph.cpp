#include "SetGraph.h"

SetGraph::SetGraph(int size) : hastTable(size) {}

void SetGraph::AddEdge(int from, int to) {
    hastTable[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return hastTable.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < hastTable[vertex].size(); ++i) {
        auto it = hastTable[vertex].find(i);
        if (it != hastTable[vertex].end()) {
            result.push_back(*it);
        }
    }
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < hastTable.size(); ++i) {
        if (hastTable[i].find(vertex) != hastTable[i].end()) {
            result.push_back(i);
        }
    }
    return result;
}

SetGraph::SetGraph(const IGraph &graph) : hastTable(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        auto next = graph.GetNextVertices(i);
        for (int j: next) {
            hastTable[i].insert(j);
        }
    }
}