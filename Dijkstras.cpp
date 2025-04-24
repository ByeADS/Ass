#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = 9999;

int graph[MAX][MAX], dist[MAX], visited[MAX];
int n, start;

int getMin() {
    int min = INF, idx = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            idx = i;
        }
    }
    return idx;
}

void dijkstra() {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = getMin();
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "\nShortest paths from location " << start << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "To location " << i << " : Distance = ";
        if (dist[i] == INF)
            cout << "Unreachable\n";
        else
            cout << dist[i] << "\n";
    }
}

int main() {
    cout << "Enter number of locations: ";
    cin >> n;

    cout << "Enter the adjacency matrix (0 if no direct path):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    cout << "Enter starting location (index 0 to " << n - 1 << "): ";
    cin >> start;

    dijkstra();

    return 0;
}