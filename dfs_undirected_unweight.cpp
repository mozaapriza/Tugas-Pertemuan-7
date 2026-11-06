#include<iostream>
#include<vector>
using namespace std;

class Graph{
    private:
        int numberVertex;
        vector<vector<int>> adjMatrix;

    public:
        Graph(int banyakTitik){
            numberVertex = banyakTitik;
            adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
        }

    void addEdge (int i, int j) {
        if (i>=0 && i<numberVertex && j>=0 && j<numberVertex) {
            adjMatrix[i][j] = 1;
            adjMatrix[j][i] = 1;
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
    }

    void dfs (int startVertex) {
        vector<bool> visited(numberVertex, false);
        dfsUntil(startVertex, visited);
    }

    void dfsUntil(int currentVertex, vector<bool>&visited) {
        visited[currentVertex] = true;
        cout << "Visited " << currentVertex << endl;

        for (int i=0; i<numberVertex; i++){
            if(adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                dfsUntil(i, visited);
            }
        }
    }
};

int main() {
    Graph graphh(8);
    
    graphh.addEdge(0,1); 
    graphh.addEdge(0,2);
    graphh.addEdge(1,3);
    graphh.addEdge(1,4);
    graphh.addEdge(2,5);
    graphh.addEdge(3,6);
    graphh.addEdge(5,7);

    graphh.printAdjMatrix();
    cout << endl;

    graphh.dfs(0);
    return 0;
}