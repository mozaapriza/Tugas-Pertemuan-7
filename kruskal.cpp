#include <iostream>
#include <vector>
#include <algorithm>
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

    void kruskal() {
        sort(edges.begin(), edges.end(),
             [](Edge a, Edge b) {
                 return a.weight < b.weight;
             });
        
        vector<int> parent(V);

        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        int totalWeight = 0;
        int edgeCount = 0;

        cout << "Edge pada MST:" << endl;

        for (Edge e : edges) {
            int u = e.src;
            int v = e.dest;

            while (parent[u] != u)
                u = parent[u];

            while (parent[v] != v)
                v = parent[v];

            if (u != v) {
                cout << e.src << " - " << e.dest
                     << " : " << e.weight << endl;

                totalWeight += e.weight;
                parent[u] = v;
                edgeCount++;

                if (edgeCount == V - 1)
                    break;
            }
        }

        if (edgeCount == V - 1)
            cout << "Total Bobot MST: " << totalWeight << endl;
        else
            cout << "Graf tidak terhubung!" << endl;
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

    graph.kruskal();

    return 0;
}