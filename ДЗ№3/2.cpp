#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <sstream>

#include "ListGraph.h"


int number_of_shortest_paths(const IGraph& graph, int from, int to) {
    enum Color { white, gray, black };
    std::vector<int> distance(graph.VerticesCount(), INT32_MAX);
    distance[from] = 0;

    std::vector<int> count(graph.VerticesCount(), 0);
    count[from] = 1;

    std::queue<int> q;
    q.push(from);

    std::vector<Color> visited(graph.VerticesCount(), white);
    visited[from] = gray;

    while (!q.empty()) {
        auto vertex = q.front();
        q.pop();

        for (int neigh : graph.GetNextVertices(vertex)) {
            switch (visited[neigh]) {
                case white: {
                    visited[neigh] = gray;
                    distance[neigh] = distance[vertex] + 1;
                    count[neigh] = count[vertex];
                    q.push(neigh);
                    break;
                }
                case gray: {
                    if (distance[neigh] == distance[vertex] + 1)
                        count[neigh] += count[vertex];
                    break;
                }
                case black: {
                    if (neigh == to)
                        break;
                }
                default:
                    break;
            }
        }
        visited[vertex] = black;
    }

    return count[to];
}

void func(std::istream &in, std::ostream & out) {
    int v, n;
    int from, to;
    in >> v >> n;
    ListGraph graph(v);
    for (int i = 0; i < n; ++i) {
        in >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    int number_from, number_to;
    in >> number_from >> number_to;

    out << number_of_shortest_paths(graph, number_from, number_to);
}

void tests() {
    {
        std::stringstream in;
        in << "4\n"
              "5\n"
              "0 1\n"
              "0 2\n"
              "1 2\n"
              "1 3\n"
              "2 3\n"
              "\n"
              "0 3\n";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "2");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}
int main() {
//    tests();
    func(std::cin, std::cout);
    return 0;
}
