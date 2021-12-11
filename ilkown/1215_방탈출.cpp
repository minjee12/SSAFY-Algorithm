#include <queue>
#include <iostream>
#include <memory.h>
using namespace std;
#define MAX 51

int map[MAX][MAX] = {};
int visited[MAX][MAX] = {};
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
int N, M;
int ans = 0;
int max_len = -99999999;

int isInside(int y, int x) {
	if (y < 0 || y >= N || x < 0 || x >= M) return 0;
	return 1;
}

struct Node {
	int y, x;
	int lev;
};

void room_escape(int y, int x) {
	queue<Node> que;
	que.push({ y,x,0 });
	visited[y][x] = 1;

	int start_y = y;
	int start_x = x;

	while (!que.empty()) {
		y = que.front().y;
		x = que.front().x;
		int lev = que.front().lev;
		que.pop();

		if (max_len < lev) {
			max_len = lev;
			ans = map[start_y][start_x] + map[y][x];
		}
		else if (max_len == lev) {
			if (ans < map[start_y][start_x] + map[y][x])
				ans = map[start_y][start_x] + map[y][x];
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];

			if (!isInside(ny, nx) || visited[ny][nx] == 1 || map[ny][nx] == 0) continue;
			visited[ny][nx] = 1;
			que.push({ ny,nx,lev + 1 });
		}
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] != 0) {
				memset(visited, 0, sizeof(visited));
				room_escape(y, x);
			}
		}
	}

	cout << ans << endl;

	return 0;
}