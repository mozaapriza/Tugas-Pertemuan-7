#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cctype>

using namespace std;

class Graph {
private:
    int numberVertex;
    vector<vector<int>> adjMatrix;

    int charToIndex(char c) {
        c = toupper(c); 
        return c - 'A';
    }

    char indexToChar(int i) {
        return 'A' + i;
    }

public:
    Graph(int banyakTitik) {
        numberVertex = banyakTitik;
        adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
    }

    bool addEdge(char u, char v) {
        int i = charToIndex(u);
        int j = charToIndex(v);

        if (i >= 0 && i < numberVertex && j >= 0 && j < numberVertex) {
            adjMatrix[i][j] = 1;
            adjMatrix[j][i] = 1; 
            return true;
        } else {
            cout << "Error! Vertex tidak valid! Harap masukkan huruf A sampai " 
                 << indexToChar(numberVertex - 1) << ".\n";
            return false;
        }
    }

    void printAdjMatrix() {
        cout << "\nADJACENCY MATRIX\n"; 
        cout << "    ";
        for (int i = 0; i < numberVertex; i++) {
            cout << indexToChar(i) << " ";
        }
        cout << "\n  +-------------+\n";

        for (int i = 0; i < numberVertex; i++) {
            cout << indexToChar(i) << " | ";
            for (int j = 0; j < numberVertex; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool bfs(char startChar) {
        int startVertex = charToIndex(startChar);

        if (startVertex < 0 || startVertex >= numberVertex) {
            cout << "Error! Vertex awal tidak valid! Harap masukkan huruf A sampai "
                 << indexToChar(numberVertex - 1) << ".\n";
            return false; 
        }

        vector<bool> visited(numberVertex, false);
        queue<int> titikVisit;

        visited[startVertex] = true;
        titikVisit.push(startVertex);

        cout << "\nHASIL PENELUSURAN (BFS) : \n";
        cout << "Vertex Awal : " << indexToChar(startVertex) << "\n";
        cout << "Urutan Visit: ";

        while (!titikVisit.empty()) {
            int currentVertex = titikVisit.front();
            titikVisit.pop();

            cout << indexToChar(currentVertex);
            
            if (!titikVisit.empty() || hasUnvisitedNeighbors(currentVertex, visited)) {
                cout << " -> ";
            }

            for (int i = 0; i < numberVertex; i++) {
                if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    titikVisit.push(i);
                }
            }
        }
        cout << endl;
        return true; 
    }

private:
    bool hasUnvisitedNeighbors(int current, const vector<bool>& visited) {
        for (int i = 0; i < numberVertex; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) return true;
        }
        return false;
    }
};

int main() {
    Graph graphh(6); 
    int jumlahEdge;

    cout << "=== PROGRAM BFS GRAF TIDAK BERARAH ===\n";
    cout << "Masukkan jumlah edge yang ingin dibuat: ";
    cin >> jumlahEdge;

    cout << "\nMasukkan Pasangan Edge (Contoh: A B)\n";
    for (int i = 0; i < jumlahEdge; ) {
        char u, v;
        cout << "Edge ke-" << (i + 1) << ": ";
        cin >> u >> v;

        if (graphh.addEdge(u, v)) {
            i++;
        }
    }

    graphh.printAdjMatrix();

    char startVertex;
    bool isInputValid = false;

    while (!isInputValid) {
        cout << "Masukkan vertex awal penelusuran (A-F): ";
        cin >> startVertex;

        isInputValid = graphh.bfs(startVertex);
    }

    return 0;
}