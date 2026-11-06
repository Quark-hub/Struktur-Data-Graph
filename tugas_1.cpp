#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class GraphBFS {
private:
    int numberVertex;
    vector<vector<int>> adjMatrix;

public:
    GraphBFS(int banyakTitik) {
        numberVertex = banyakTitik;
        adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
    }

    void addEdge(int i, int j) {
        if (i >= 0 && i < numberVertex && j >= 0 && j < numberVertex) {
            adjMatrix[i][j] = 1;
            adjMatrix[j][i] = 1;
        } else {
            cout << "Index nonvalid" << endl;
        }
    }

    void printAdjMatrix() {
        cout << "\nAdjacency Matrix:\n  ";
        for (int i = 0; i < numberVertex; i++) cout << (char)(i + 'A') << " ";
        cout << endl;
        for (int i = 0; i < numberVertex; i++) {
            cout << (char)(i + 'A') << " ";
            for (int j = 0; j < numberVertex; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bfs(int startVertex) {
        vector<bool> visited(numberVertex, false);
        queue<int> titikVisit;

        visited[startVertex] = true;
        titikVisit.push(startVertex);

        cout << "Urutan vertex yang dikunjungi (BFS): ";
        while (!titikVisit.empty()) {
            int currentVertex = titikVisit.front();
            titikVisit.pop();
            cout << (char)(currentVertex + 'A') << " ";

            for (int i = 0; i < numberVertex; i++) {
                if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    titikVisit.push(i);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int n = 6;
    GraphBFS graphh(n);
    
    int numEdges;
    cout << "Masukkan jumlah edge yang ingin dimasukkan: ";
    cin >> numEdges;
    
    cout << "Masukkan edge dalam bentuk pasangan huruf (contoh: A B):\n";
    for (int k = 0; k < numEdges; k++) {
        char uChar, vChar;
        cin >> uChar >> vChar;
        int u = uChar - 'A';
        int v = vChar - 'A';
        graphh.addEdge(u, v);
    }

    graphh.printAdjMatrix();
    cout << endl;

    char startChar;
    cout << "Masukkan vertex awal (A-F): ";
    cin >> startChar;
    int startVertex = startChar - 'A';

    graphh.bfs(startVertex);
    return 0;
}