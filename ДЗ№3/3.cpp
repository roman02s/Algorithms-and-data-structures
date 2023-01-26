#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <sstream>


struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, int time) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
//    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int vertices_count) {
        this->graph.resize(vertices_count);
    }
    ListGraph(const IGraph& graph) {}

    ~ListGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to, int time)  {
        graph[from].push_back(std::pair<int, int>(to, time));
    }

    int VerticesCount() const {
        return graph.size();
    }

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const {
        std::vector<std::pair<int, int>> result;
        result.resize(graph[vertex].size());
        std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
        return result;
    }

private:
    std::vector<std::vector<std::pair<int, int>>> graph;
};


int shortest_paths(const IGraph& graph, int from, int to) {
    std::vector<int> distance(graph.VerticesCount(), INT32_MAX);
    distance[from] = 0;
    std::set<std::pair<int, int>> q;
    q.emplace(0, from);
    while (!q.empty()) {
        auto v = q.begin();
        auto children = graph.GetNextVertices(v->second);
        for (auto next : children) {
            if (distance[next.first] > distance[v->second] + next.second) {
                auto vertexQueue = q.find(std::pair<int, int>(distance[next.first], next.first));
                if (vertexQueue != q.end()) {
                    q.erase(vertexQueue);
                }
                distance[next.first] = distance[v->second] + next.second;
                q.insert(std::pair<int, int>(distance[next.first], next.first));
            }
        }
        q.erase(q.find(*v));
    }
    return distance[to];
}

void func(std::istream &in, std::ostream & out) {
    int v, n;
    int from, to, time;
    in >> v >> n;
    ListGraph graph(v);
    for (int i = 0; i < n; ++i) {
        in >> from >> to >> time;
        graph.AddEdge(from, to, time);
        graph.AddEdge(to, from, time);
    }

    int number_from, number_to;
    in >> number_from >> number_to;

    out << shortest_paths(graph, number_from, number_to);
}

void tests() {
    {
        std::stringstream in;
        in << "6\n"
              "9\n"
              "0 3 1\n"
              "0 4 2\n"
              "1 2 7\n"
              "1 3 2\n"
              "1 4 3\n"
              "1 5 3\n"
              "2 5 3\n"
              "3 4 4\n"
              "3 5 6\n"
              "0 2\n"
              "";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "9");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}
int main() {
//    tests();
    func(std::cin, std::cout);
    return 0;
}
