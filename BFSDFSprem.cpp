#include <iostream>
using namespace std;

#define MAX_NODES 100

class Graph {
private:
    int vertices;
    int arr[MAX_NODES][MAX_NODES];

public:
    Graph(int v) {
        vertices = v;
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                arr[i][j] = 0;
            }
        }
    }

    void addEdge(int s, int d) {
        arr[s][d] = 1;
        arr[d][s] = 1;
    }

    void BFS(int start) {
        int visited[MAX_NODES] = {0};  
        int queue[MAX_NODES];
        int front = 0, rear = 0;

        visited[start] = 1;
        queue[rear++] = start;

        while (front < rear) {
            int node = queue[front++];
            cout << node << " ";

            for (int i = 0; i < vertices; i++) {
                if (arr[node][i] == 1 && visited[i] == 0) {
                    visited[i] = 1;
                    queue[rear++] = i;
                }
            }
        }
        cout << endl;
    }

    void DFS(int start) {
        int visited[MAX_NODES] = {0}; 
        int stack[MAX_NODES];
        int top = -1;

        visited[start] = 1;
        stack[++top] = start;

        while (top >= 0) {
            int node = stack[top--];
            cout << node << " ";

            for (int i = 0; i < vertices; i++) {
                if (arr[node][i] == 1 && visited[i] == 0) {
                    visited[i] = 1;
                    stack[++top] = i;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int choice;
    char ch;
    int vertices, edges;
    
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    Graph g(vertices);

    for (int i = 0; i < edges; i++) {
        int s, d;
        cout << "Enter source and destination: ";
        cin >> s >> d;
        g.addEdge(s, d);
    }

    do {
        cout << "Enter the choice \n1. Breadth First Search(BFS)\n2. Depth First Search(DFS): ";
        cin >> choice;
        int start;
        switch (choice) {
            case 1:
                cout << "Enter the starting node: ";
                cin >> start;
                g.BFS(start);
                break;
            case 2:
                cout << "Enter the starting node: ";
                cin >> start;
                g.DFS(start);
                break;
            default:
                cout << "Invalid choice!\n";
        }
        cout << "Do you want to continue (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');  

    return 0;
}
