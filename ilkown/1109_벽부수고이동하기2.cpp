#include <queue>
#include <iostream>
#include <string>
using namespace std;

int N, M, K;
int map[1001][1001] = {};
int visited[11][1001][1001] = {};
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
int ans = -1;

struct Path {
	int y, x;
	int cnt = 0;
};

int isInside(int y, int x) {
	if (y<1 || y>N || x<1|| x>M) return 0;

	return 1;
}

void bfs() {
	queue<Path> que;
	que.push({ 1,1,0 });
	visited[0][1][1] = 1;
	int cnt = 0;

	while (!que.empty()) {
		int y = que.front().y;
		int x = que.front().x;
		cnt = que.front().cnt;
		que.pop();

		if (y == N && x == M) break;

		for (int i = 0; i < 4; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];

			if (!isInside(ny, nx) || visited[cnt][ny][nx] != 0)continue;

			if (map[ny][nx] == 0) {
				visited[cnt][ny][nx] = visited[cnt][y][x] + 1;
				que.push({ ny,nx,cnt });
			}
			else if (map[ny][nx] == 1) {
				if (cnt < K) {
					visited[cnt + 1][ny][nx] = visited[cnt][y][x] + 1;
					que.push({ ny,nx,cnt + 1 });
				}
			}
		}
	}

	if (visited[cnt][N][M] != 0) ans = visited[cnt][N][M];
}

int main() {

	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		string str;
		cin >> str;

		for (int j = 1; j <= M; j++) {
			map[i][j] = str[j - 1] - '0';
		}
	}

	bfs();

	cout << ans << endl;

	return 0;
}
