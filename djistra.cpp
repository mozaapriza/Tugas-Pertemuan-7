#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int jumlahVertex) {
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    void dijkstra(int source) {
        vector<int> distance(V, INT_MAX);
        vector<bool> visited(V, false);
        distance[source] = 0; 

        for (int i = 0; i < V; i++) {
            int u = -1;
            
            for (int j = 0; j < V; j++) {
                
                if (!visited[j] &&
                    (u == -1 || distance[j] < distance[u])) {
                    u = j;
                }
            }

            if (u == -1 || distance[u] == INT_MAX)
                break;

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v]) {
                    int newDistance = distance[u] + adjMatrix[u][v];

                    if (newDistance < distance[v]) {
                        distance[v] = newDistance; 
                    }
                }
            }
        }

        cout << "Jarak terpendek dari vertex " << source << ":" << endl;

        for (int i = 0; i < V; i++) {
            if (distance[i] == INT_MAX)
                cout << i << " : Tidak terjangkau" << endl;
            else
                cout << i << " : " << distance[i] << endl;
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

    graph.dijkstra(0);

    return 0;
}