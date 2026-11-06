#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cctype>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

    int charToIndex(char c) {
        c = toupper(c);
        return c - 'A';
    }

    char indexToChar(int i) {
        return 'A' + i;
    }

    void getPathVector(int current, const vector<int>& parent, vector<char>& path) {
        if (current == -1) return;
        getPathVector(parent[current], parent, path);
        path.push_back(indexToChar(current));
    }

public:
    Graph(int jumlahVertex) {
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(char uChar, char vChar, int weight) {
        int u = charToIndex(uChar);
        int v = charToIndex(vChar);

        if (u >= 0 && u < V && v >= 0 && v < V) {
            adjMatrix[u][v] = weight;
            adjMatrix[v][u] = weight;
        }
    }

    void dijkstraFromSource(char sourceChar) {
        int source = charToIndex(sourceChar);
        if (source < 0 || source >= V) {
            cout << "Lokasi asal tidak valid!\n";
            return;
        }

        vector<int> distance(V, INT_MAX);
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);

        distance[source] = 0;

        for (int i = 0; i < V; i++) {
            int u = -1;
            for (int j = 0; j < V; j++) {
                if (!visited[j] && (u == -1 || distance[j] < distance[u])) {
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
                        parent[v] = u;
                    }
                }
            }
        }

        cout << "RUTE TERPENDEK DARI LOKASI " << sourceChar << " KE SEMUA LOKASI:\n";
        for (int i = 0; i < V; i++) {
            cout << "Ke Lokasi " << indexToChar(i) << " | Jarak: ";
            if (distance[i] == INT_MAX) {
                cout << "Tidak terjangkau\n";
            } else {
                cout << distance[i] << " km | Rute: ";
                vector<char> path;
                getPathVector(i, parent, path);
                for (size_t p = 0; p < path.size(); p++) {
                    cout << path[p];
                    if (p < path.size() - 1) cout << " -> ";
                }
                cout << endl;
            }
        }
    }

    void cariRekomendasiRute(char startChar, char targetChar) {
        int start = charToIndex(startChar);
        int target = charToIndex(targetChar);

        if (start < 0 || start >= V || target < 0 || target >= V) {
            cout << "Lokasi asal atau tujuan tidak valid!\n";
            return;
        }

        vector<int> distance(V, INT_MAX);
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);

        distance[start] = 0;

        for (int i = 0; i < V; i++) {
            int u = -1;
            for (int j = 0; j < V; j++) {
                if (!visited[j] && (u == -1 || distance[j] < distance[u])) {
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
                        parent[v] = u;
                    }
                }
            }
        }

        cout << "\nREKOMENDASI RUTE TERCEPAT:\n";
        if (distance[target] == INT_MAX) {
            cout << "Rute tidak ditemukan / tidak terjangkau.\n";
        } else {
            cout << "Total Jarak: " << distance[target] << " km\n";
            cout << "Rute: ";
            vector<char> path;
            getPathVector(target, parent, path);
            for (size_t p = 0; p < path.size(); p++) {
                cout << path[p];
                if (p < path.size() - 1) cout << " -> ";
            }
            cout << "\n";
        }
    }
};

int main() {
    Graph navigasiKota(6);

    navigasiKota.addEdge('A', 'B', 4);
    navigasiKota.addEdge('A', 'C', 2);
    navigasiKota.addEdge('B', 'C', 1);
    navigasiKota.addEdge('B', 'D', 5);
    navigasiKota.addEdge('B', 'E', 3);
    navigasiKota.addEdge('C', 'D', 8);
    navigasiKota.addEdge('C', 'E', 6);
    navigasiKota.addEdge('D', 'E', 2);
    navigasiKota.addEdge('D', 'F', 4);
    navigasiKota.addEdge('E', 'F', 3);

    cout << "=== SIMULASI NAVIGASI KOTA (DIJKSTRA) ===\n\n";

    navigasiKota.dijkstraFromSource('A');

    char asal, tujuan;
    cout << "\nMasukkan Lokasi Asal (A-F): ";
    cin >> asal;
    cout << "Masukkan Lokasi Tujuan (A-F): ";
    cin >> tujuan;

    navigasiKota.cariRekomendasiRute(asal, tujuan);

    return 0;
}