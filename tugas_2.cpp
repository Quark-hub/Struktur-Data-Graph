#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

class GraphDijkstra {
private:
    int V;
    vector<vector<int>> adjMatrix;

    void printPath(const vector<int>& parent, int j, string& pathStr) {
        if (parent[j] == -1) {
            pathStr += (char)(j + 'A');
            return;
        }
        printPath(parent, parent[j], pathStr);
        pathStr += " -> " + string(1, (char)(j + 'A'));
    }

public:
    GraphDijkstra(int jumlahVertex) {
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    void dijkstra(int source, int destination = -1) {
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

        if (destination != -1) {
            cout << "\nRute tercepat dari " << (char)(source + 'A') << " ke " << (char)(destination + 'A') << ":" << endl;
            if (distance[destination] == INT_MAX) {
                cout << "Tidak terjangkau!" << endl;
            } else {
                string pathStr = "";
                printPath(parent, destination, pathStr);
                cout << "Total Jarak : " << distance[destination] << " km" << endl;
                cout << " Jalur Rute : " << pathStr << endl;
            }
        } else {
            cout << "Jarak terpendek dari lokasi " << (char)(source + 'A') << " ke semua lokasi:" << endl;
            for (int i = 0; i < V; i++) {
                string pathStr = "";
                printPath(parent, i, pathStr);
                if (distance[i] == INT_MAX)
                    cout << "Ke " << (char)(i + 'A') << " : Tidak terjangkau" << endl;
                else
                    cout << "Ke " << (char)(i + 'A') << " : Jarak = " << distance[i] << " km | Rute: " << pathStr << endl;
            }
        }
    }
};

int main() {
    GraphDijkstra graph(6);

    
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(1, 4, 3);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 6);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 4);
    graph.addEdge(4, 5, 3);
       
    graph.dijkstra(0);

    char startChar, destChar;
    cout << "Masukkan lokasi asal (A-F): ";
    cin >> startChar;
    cout << "Masukkan lokasi tujuan (A-F): ";
    cin >> destChar;

    int src = startChar - 'A';
    int dest = destChar - 'A';

    if (src >= 0 && src < 6 && dest >= 0 && dest < 6) {
        graph.dijkstra(src, dest);
    } else {
        cout << "Lokasi tidak valid! Masukkan huruf antara A sampai F." << endl;
    }

    return 0;
}