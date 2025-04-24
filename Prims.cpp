#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = 9999;

int cost[MAX][MAX];
bool visited[MAX];
int parent[MAX], key[MAX];
int n;

int minKey() {
    int min = INF, idx = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && key[i] < min) {
            min = key[i];
            idx = i;
        }
    }
    return idx;
}

void prim() {
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = minKey();
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (cost[u][v] && !visited[v] && cost[u][v] < key[v]) {
                parent[v] = u;
                key[v] = cost[u][v];
            }
        }
    }

    cout << "\nMinimum Spanning Tree (MST):\n";
    for (int i = 1; i < n; i++) {
        cout << "Dept " << parent[i] << " - Dept " << i << " : Distance = " << cost[i][parent[i]] << "\n";
    }
}

int main() {
    cout << "Enter number of departments: ";
    cin >> n;

    cout << "Enter distance matrix (0 if no direct path):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    prim();

    return 0;
}