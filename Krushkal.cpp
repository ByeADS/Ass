#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = 999; // A large number representing no connection

struct Edge {
    int u, v, w;
};

Edge edges[MAX * MAX]; // Edge list extracted from matrix
int parent[MAX];
int n, edgeCount = 0;

void sortEdges() {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = i + 1; j < edgeCount; j++) {
            if (edges[i].w > edges[j].w) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

int find(int x) {
    while (parent[x] != x)
        x = parent[x];
    return x;
}

void kruskal() {
    int mstWeight = 0;

    for (int i = 0; i < n; i++)
        parent[i] = i;

    sortEdges();

    cout << "\nMinimum Spanning Tree:\n";
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        int pu = find(u);
        int pv = find(v);

        if (pu != pv) {
            cout << "Dept " << u << " - Dept " << v << " : Distance = " << w << "\n";
            mstWeight += w;
            parent[pu] = pv;
        }
    }

    cout << "Total Distance of MST: " << mstWeight << "\n";
}

int main() {
    int adj[MAX][MAX];

    cout << "Enter number of departments (nodes): ";
    cin >> n;

    cout << "Enter adjacency matrix (enter " << INF << " if no path):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];

            // Avoid duplicates in undirected graph
            if (i < j && adj[i][j] != INF) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].w = adj[i][j];
                edgeCount++;
            }
        }
    }

    kruskal();

    return 0;
}
