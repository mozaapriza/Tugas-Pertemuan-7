#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
    int src, dest, weight;
};

class Graph {
private:
    int V;
    vector<Edge> edges;

public:
    Graph(int jumlahVertex) {
        V = jumlahVertex;
    }

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    void bellmanFord(int source) {
        vector<int> distance(V, INT_MAX);
        distance[source] = 0;

        for (int i = 0; i < V - 1; i++) {
            for (Edge e : edges) {

                if (distance[e.src] != INT_MAX &&
                    distance[e.src] + e.weight < distance[e.dest]) {
                    distance[e.dest] = distance[e.src] + e.weight;
                }
            }
        }

        for (Edge e : edges) {
            if (distance[e.src] != INT_MAX &&
                distance[e.src] + e.weight < distance[e.dest]) {

                cout << "Graf memiliki Negative Weight Cycle!" << endl;
                return;
            }
        }

        cout << "Jarak terpendek dari vertex " << source << ":" << endl;
        
        for (int i = 0; i < V; i++) {
            if (distance[i] == INT_MAX)
                cout << source << " ke " << i << " : Tidak terjangkau" << endl;
            else
                cout << source << " ke " << i << " : " << distance[i] << endl;
        }
    }
};

int main() {
    Graph graph(5);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 9);

    graph.bellmanFord(0);

    return 0;
}