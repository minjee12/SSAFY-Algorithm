#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

int T;
int M, N, K;

int map[50][50] = { 0 };
int used[50][50] = { 0 };
int direct[4][2] = { 
	-1, 0,
	0, 1,
	1, 0,
	0, -1, 
};

struct node {
	int y, x;
};

void bfs(int starty, int startx) {
	queue<node> q;
	q.push({ starty, startx });
	used[starty][startx] = 1;

	while (!q.empty()) {
		node now = q.front();
		q.pop();

		for (int t = 0; t < 4; t++) {
			node next;
			next.y = now.y + direct[t][0];
			next.x = now.x + direct[t][1];
			if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) continue;
			if (used[next.y][next.x] == 1) continue;

			if (map[next.y][next.x] == 1) {
				used[next.y][next.x] = 1;
				q.push(next);
			}
		}
	}
}

int solution() {
	memset(map, 0, sizeof(map));
	memset(used, 0, sizeof(map));
	int cnt_bug = 0;
	int cnt_baechu = 0;

	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		map[y][x] = 1;
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 0 || used[y][x] == 1) continue;
			bfs(y, x);
			cnt_bug++;
			if (cnt_baechu == K) return cnt_bug;
		}
	}
	return cnt_bug;
}

int main() {
	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> M >> N >> K;
		cout << solution() << "\n";
	}

	return 0;
}