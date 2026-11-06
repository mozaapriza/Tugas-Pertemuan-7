#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int jumlahVertex){
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge (int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    int minKey(vector<int>& key, vector<bool>& mstSet) {
        int min = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

   void prim() {
    vector<int> parent(V, -1);
    vector<int> key(V, INT_MAX);
    vector<bool> mstSet(V, false);

    key[0] = 0;

    for (int count = 0; count < V; count++) {
        int u = minKey(key, mstSet);

        if (u == -1) {
            cout << "Graf tidak terhubung" << endl;
            return;
        }

        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (adjMatrix[u][v] != 0 &&
                !mstSet[v] &&
                adjMatrix[u][v] < key[v]) {

                parent[v] = u;
                key[v] = adjMatrix[u][v];
            }
        }
    }

    int totalWeight = 0;

    cout << "Edge pada MST (Prim) : " << endl;

    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i 
             << " : " << adjMatrix[i][parent[i]] << endl;

        totalWeight += adjMatrix[i][parent[i]];
    }

    cout << "Total bobot MST : " << totalWeight << endl;
}
};

int main() {
    Graph graphh(5);

    graphh.addEdge(0,1,2);
    graphh.addEdge(0,3,6);
    graphh.addEdge(1,2,3);
    graphh.addEdge(1,3,8);
    graphh.addEdge(1,4,5);
    graphh.addEdge(2,4,7);
    graphh.addEdge(3,4,9);

    graphh.prim();
    return 0;
}