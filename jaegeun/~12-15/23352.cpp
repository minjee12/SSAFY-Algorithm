// 방탈출
// https://www.acmicpc.net/problem/23352

#define MAX 50

#include <iostream>
#include <queue>

using namespace std;

int N, M;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int code = 0;
int g_max_step = 0;
int board[MAX][MAX];

void bfs(int x, int y) {
	int visited[MAX][MAX] = { 0, };
	int max_step = 0;
	queue<pair<int, int>> q;
	visited[x][y] = 1;
	q.push({ x, y });
	while (q.size()) {
		int cx = q.front().first;
		int cy = q.front().second;
		
		q.pop();

		max_step = max(max_step, visited[cx][cy]);

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (board[nx][ny] == 0) continue;
			if (visited[nx][ny]) continue;

			q.push({ nx, ny });
			visited[nx][ny] = visited[cx][cy] + 1;
		}
	}
	
	if (max_step < g_max_step) return;
	else {
		if (max_step > g_max_step) code = 0;
		g_max_step = max_step;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (visited[i][j] == g_max_step) {
					code = max(code, board[x][y] + board[i][j]);
				}
			}
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j]) {
				bfs(i, j);
			}
		}
	}
	cout << code;
	return 0;
}
