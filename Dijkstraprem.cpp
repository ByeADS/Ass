#include <iostream>
#define V 4
#define INF 999999

using namespace std;

class Dijkstra {
    int graph[V][V];
    int n;

public:
    Dijkstra(int size) {
        n = size;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++){
                if(i==j)
                    graph[i][j] = 0;
                else
                    graph[i][j] = INF;
            }
    }

    void createGraph() {
        int edges;
        cout << "Enter number of edges: ";
        cin >> edges;

        cout << "Enter edges in format: source destination weight\n";
        for (int i = 0; i < edges; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u][v] = w;
            graph[v][u] = w; // Remove this line if the graph is directed
        }
    }

    void dijkstraAlgo(int src) {
        int dist[V];
        bool visited[V];

        for (int i = 0; i < n; i++) {
            dist[i] = INF;
            visited[i] = false;
        }

        dist[src] = 0;

        for (int count = 0; count < n - 1; count++) {
            int u = minDistance(dist, visited);
            if (u == -1) break;
            visited[u] = true;

            for (int v = 0; v < n; v++) {
                if (graph[u][v] != 0 && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        // Output the shortest distances
        cout << "Shortest distances from source " << src << ":\n";
        for (int i = 0; i < n; i++) {
            cout << "To vertex " << i << ": ";
            if (dist[i] == INF)
                cout << "INF" << endl;
            else
                cout << dist[i] << endl;
        }
    }

private:
    int minDistance(int dist[], bool visited[]) {
        int min = INF, min_index = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] <= min) {
                min = dist[i];
                min_index = i;
            }
        }

        return min_index;
    }

};

int main() {
    Dijkstra d(V);
    d.createGraph();
    d.dijkstraAlgo(0);
    return 0;
}
