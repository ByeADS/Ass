#include <iostream>
using namespace std;

const int MAX = 100;
int maze[MAX][MAX];
bool visited[MAX][MAX];
int parent[MAX][MAX][2]; // Stores parent coordinates
int n, m;

// Directions: right, down, left, up
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

// Queue for BFS
struct Queue {
    int x, y;
};
Queue queue[MAX * MAX];
int front = 0, rear = 0;

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m &&
           maze[x][y] == 1 && !visited[x][y];
}

void bfs(int x, int y) {
    queue[rear++] = {x, y};
    visited[x][y] = true;
    parent[x][y][0] = -1; // No parent
    parent[x][y][1] = -1;

    while (front < rear) {
        Queue curr = queue[front++];

        if (curr.x == n - 1 && curr.y == m - 1)
            return;

        for (int d = 0; d < 4; d++) {
            int nx = curr.x + dx[d];
            int ny = curr.y + dy[d];

            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                queue[rear++] = {nx, ny};
                parent[nx][ny][0] = curr.x;
                parent[nx][ny][1] = curr.y;
            }
        }
    }
}

void printPath(int x, int y) {
    if (x == -1 || y == -1)
        return;
    printPath(parent[x][y][0], parent[x][y][1]);
    cout << "(" << x << ", " << y << ") ";
}

int main() {
    cout << "Enter maze dimensions (rows and columns): ";
    cin >> n >> m;

    cout << "Enter maze matrix (1 = open, 0 = blocked):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    bfs(0, 0);

    if (!visited[n - 1][m - 1])
        cout << "No path found.\n";
    else {
        cout << "\nPath found (from start to goal):\n";
        printPath(n - 1, m - 1);
        cout << "\n";
    }

    return 0;
}
