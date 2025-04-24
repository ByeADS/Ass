#include <iostream>
using namespace std;

const int MAX = 100;
int maze[MAX][MAX];
bool visited[MAX][MAX];
int n, m;
bool found = false;

int dx[] = {0, 1, 0, -1};  // Right, Down, Left, Up
int dy[] = {1, 0, -1, 0};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y];
}

void dfs(int x, int y) {
    if (x == n - 1 && y == m - 1) {
        found = true;
        cout << "(" << x << ", " << y << ") ";
        return;
    }

    visited[x][y] = true;

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (isValid(nx, ny)) {
            dfs(nx, ny);
            if (found) {
                cout << "(" << x << ", " << y << ") ";
                return;
            }
        }
    }
}

int main() {
    cout << "Enter maze dimensions (rows and columns): ";
    cin >> n >> m;

    cout << "Enter maze matrix (0 = open, 1 = blocked):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    dfs(0, 0);

    if (!found)
        cout << "No path found.\n";
    else
        cout << "\nPath found (from goal to start).\n";

    return 0;
}