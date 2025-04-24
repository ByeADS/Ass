#include <iostream>
using namespace std;

const int MAX = 100;

struct Edge {
    int u, v, w;
};

Edge edges[MAX];
int parent[MAX];
int n, e;

void sortEdges() {
    for (int i = 0; i < e - 1; i++) {
        for (int j = i + 1; j < e; j++) {
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
    for (int i = 0; i < e; i++) {
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
    cout << "Enter number of departments (nodes): ";
    cin >> n;
    cout << "Enter number of paths (edges): ";
    cin >> e;

    cout << "Enter each edge as: from to distance\n";
    for (int i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    kruskal();

    return 0;
}