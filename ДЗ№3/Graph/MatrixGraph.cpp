#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int size) : graph(size) {}

void MatrixGraph::AddEdge(int from, int to) {
    graph[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return graph.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[vertex][i]) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[i][vertex]) {
            result.push_back(i);
        }
    }
    return result;
}

MatrixGraph::MatrixGraph(const IGraph &graph): graph(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        auto next = graph.GetNextVertices(i);
        for (int j : next) {
            this->graph[i][j] = true;
        }
    }

}
