#include<iostream>
#include<vector>
using namespace std;

class Graph {
    private:
        int numberVertex; // menyimpan jumlah vertex
        vector<vector<int>> adjMatrix; // menyimpan hubungn antar vertex dalam matrix 2d

    public:
        Graph(int banyakTitik){
            numberVertex = banyakTitik;
            adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
        }

    // fungsi untuk menghubungkan tiap titik
    void addEdge(int i, int j) {
        if (i >= 0 && i < numberVertex && j >= 0 && j < numberVertex) {
            adjMatrix[i][j] = 1; // febrian -> meisrik
            adjMatrix[j][i] = 0; // mesrik -> febrian
        } else {
            cout << "Index nonvalid" << endl;
        }
    }

    void printAdjMatrix() {
        for (int i = 0; i < numberVertex; i++) {
            for (int j = 0; j < numberVertex; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
        // x x
        // x x
    }
};

int main() {
    Graph graphh(5); // vertex index = 0, 1, 2, 3, 4

    graphh.addEdge(0,1);
    graphh.addEdge(0,2);
    graphh.addEdge(1,3);
    graphh.addEdge(1,4);
    graphh.addEdge(2,3);
    graphh.addEdge(3,4);
    graphh.printAdjMatrix();
}