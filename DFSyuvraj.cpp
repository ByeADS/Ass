#include <iostream>
using namespace std;

const int MAX = 100;
int maze[MAX][MAX];
bool visited[MAX][MAX];
int n, m;
bool found = false;

// directions: right, down, left, up (clockwise)
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

// Function to check if a cell (x, y) is valid to move into
bool isValid(int x, int y) 
{
    return x >= 0 && x < n && y >= 0 && y < m &&
           maze[x][y] == 1 && !visited[x][y];
}

// Recursive DFS function to explore the maze
void dfs(int x, int y) 
{
    // If goal (bottom-right corner) is reached
    if (x == n - 1 && y == m - 1) 
    {
        found = true;
        cout << "(" << x << ", " << y << ") ";
        return;
    }

    // Mark the current cell as visited
    visited[x][y] = true;

    // Explore all 4 possible directions
    for (int d = 0; d < 4; d++) 
    {
        int nx = x + dx[d]; // New x-coordinate
        int ny = y + dy[d]; // New y-coordinate

        // If the neighbor cell is valid, explore it
        if (isValid(nx, ny)) 
        {
            dfs(nx, ny);
            // If path is found, print current cell and return
            if (found) 
            {
                cout << "(" << x << ", " << y << ") ";
                return;
            }
        }
    }
}

int main() 
{
    cout << "Enter maze dimensions (rows and columns): ";
    cin >> n >> m;

    cout << "Enter maze matrix (1 = open, 0 = blocked):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    dfs(0, 0);

    if (!found)
        cout << "No path found.\n";
    else
        cout << "\nPath found (from goal to start).\n";

    return 0;
}
