// 벽 부수고 이동하기
// https://www.acmicpc.net/problem/2206

#include <iostream>
#include <queue>

#define MAX 1000
using namespace std;

typedef struct {
	int x;
	int y;
}pos;

int N, M;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int board[MAX][MAX];
int visited[2][MAX][MAX];

int bfs() {
	queue<pair<pair<int,int>, int>> q;
	// queue<pair<pos, int>> q;
	q.push({ { 0, 0 }, 0 });
	visited[0][0][0] = 1;
	visited[1][0][0] = 1;

	while (q.size()) {
		int cx = q.front().first.first;
		int cy = q.front().first.second;
		int cw = q.front().second; // 벽 부순 경우 1, 아닌 경우 0

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx == N - 1 && ny == M - 1) return visited[cw][cx][cy] + 1;

			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (visited[cw][nx][ny]) continue;

			if (board[nx][ny] == 1 && cw == 0) { // 다음 위치가 벽이고, 벽을 부수지 않았을 때
				if (!visited[1][nx][ny]) {
					q.push({ { nx,ny }, 1 });
					visited[1][nx][ny] = visited[cw][cx][cy] + 1;
				}
			}
			else if (board[nx][ny] == 1 && cw == 1) continue;
			else if (board[nx][ny] != 1) {
				q.push({ {nx, ny}, cw });
				visited[cw][nx][ny] = visited[cw][cx][cy] + 1;
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		string inp; cin >> inp;
		for (int j = 0; j < M; j++) {
			board[i][j] = int(inp[j] - '0');
		}
	}
	if (N == 1 && M == 1) {
		cout << 1;
	}
	else {
		cout << bfs();
	}
	return 0;
}