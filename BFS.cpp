#include <iostream>
using namespace std;

const int MAX = 100;
int maze[MAX][MAX], n, m;
bool visited[MAX][MAX];
int prevX[MAX][MAX], prevY[MAX][MAX];
int dx[] = {0, 1, 0, -1}; // right, down, left, up
int dy[] = {1, 0, -1, 0};

struct QueueNode {
    int x, y;
};

QueueNode queue[MAX * MAX];
int front = 0, rear = 0;

void enqueue(int x, int y) {
    queue[rear].x = x;
    queue[rear].y = y;
    rear++;
}

QueueNode dequeue() {
    return queue[front++];
}

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y];
}

void printPath(int x, int y) {
    if (x == -1 || y == -1) return;
    printPath(prevX[x][y], prevY[x][y]);
    cout << "(" << x << ", " << y << ") ";
}

void bfs(int sx, int sy) {
    enqueue(sx, sy);
    visited[sx][sy] = true;
    prevX[sx][sy] = -1;
    prevY[sx][sy] = -1;

    while (front < rear) {
        QueueNode cur = dequeue();
        int x = cur.x, y = cur.y;

        if (x == n - 1 && y == m - 1) {
            cout << "Shortest path:\n";
            printPath(x, y);
            return;
        }

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (isValid(nx, ny)) {
                enqueue(nx, ny);
                visited[nx][ny] = true;
                prevX[nx][ny] = x;
                prevY[nx][ny] = y;
            }
        }
    }

    cout << "No path found.\n";
}

int main() {
    cout << "Enter maze size (rows and cols): ";
    cin >> n >> m;

    cout << "Enter maze (0=open, 1=blocked):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    bfs(0, 0);

    return 0;
}