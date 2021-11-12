#include <iostream>
#include <string>
#include <queue>
using namespace std;

int n, m, k;
int map[1001][1001];
int visited[1001][1001][11] = { 0, };
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

struct info {
	int y;
	int x;
	int dis;
	int cnt; //벽 부순 개수
};


int bfs() {
	queue<info> q;
	q.push({ 1, 1, 1, 0 });
	visited[1][1][0] = 1;

	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int d = q.front().dis;
		int c = q.front().cnt;
		q.pop();

		if (y == n && x == m) return d;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny <= 0 || nx <= 0 || ny > n || nx > m) continue;
			if (!visited[ny][nx][c] && map[ny][nx] == 0) {
				q.push({ ny, nx, d + 1, c });
				visited[ny][nx][c] = 1;
			}
			else if (!visited[ny][nx][c+1] && map[ny][nx] == 1 && c < k) {
				q.push({ ny, nx, d + 1, c + 1 });
				visited[ny][nx][c + 1] = 1;
			}
		}
	}

	return -1;
}

int main() {
	//input
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.size(); j++) {
			map[i][j + 1] = str[j] - '0';
		}
	}

	int res = bfs();
	cout << res << "\n";

	return 0;
}