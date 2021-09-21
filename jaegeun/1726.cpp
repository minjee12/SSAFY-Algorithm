#include <iostream>
#include <queue>

using namespace std;

struct robot {
    int x;
    int y;
    int d;
};

int N, M;
int sx, sy, sd, ex, ey, ed;
int board[100][100];
int visited[100][100][4];
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

void bfs() {
    queue<robot> q;
    q.push({ sx - 1, sy - 1, sd - 1 });
    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int d = q.front().d; 
        q.pop();
        if (x == ex - 1 && y == ey - 1 && d == ed - 1) {
            cout << visited[x][y][d];
            return;
        }
        for (int i = 1; i <= 3; i++) {
            int nx = x + dx[d] * i, ny = y + dy[d] * i;
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) break;
            if (board[nx][ny]) break;
            if (visited[nx][ny][d]) continue;
            q.push({ nx, ny, d });
            visited[nx][ny][d] = visited[x][y][d] + 1;
        }
        for (int i = 0; i < 4; i++) {
            if (i == d) continue;
            int k = (i + d) % 4 == 1 ? 2 : 1;
            if (visited[x][y][i]) continue;
            q.push({ x, y, i });
            visited[x][y][i] = visited[x][y][d] + k;
        }
    }
}

int main() {
    freopen_s(new FILE *, "text.txt", "r", stdin);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> board[i][j];
        }
    }
    cin >> sx >> sy >> sd;
    cin >> ex >> ey >> ed;
    
    bfs();
    return 0;
}