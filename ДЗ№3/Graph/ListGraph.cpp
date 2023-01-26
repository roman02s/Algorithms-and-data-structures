#include "ListGraph.h"

ListGraph::ListGraph(int size): graph(size) {}

ListGraph::ListGraph(const IGraph &graph): graph(graph.VerticesCount()) {
    for(int i = 0;i < graph.VerticesCount();++i) {
        this->graph[i] = graph.GetNextVertices(i);
    }
}
void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
}
int ListGraph::VerticesCount() const {
    return graph.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    result.resize(graph[vertex].size());
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (size_t i = 0; i < graph.size(); ++i) {
        for (auto child : graph[i]) {
            if (child == vertex) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}