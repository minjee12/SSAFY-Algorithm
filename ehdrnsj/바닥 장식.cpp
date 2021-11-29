#include <iostream>
#include <queue>
using namespace std;

int M, N;

char map[50][51];
int used[50][50];

int direct[2][2] = { 0, 1, 1, 0 };
int cnt;

struct node {
	int y, x;
};

void dfs(int starty, int startx, int direction) {
	queue<node> q;
	q.push({ starty, startx });

	while (!q.empty()) {
		node now = q.front();
		q.pop();

		used[now.y][now.x] = 1;

		node next;
		next.y = now.y + direct[direction][0];
		next.x = now.x + direct[direction][1];

		if (next.y >= M || next.x >= N) continue;

		if (map[now.y][now.x] == map[next.y][next.x]) {
			q.push(next);
		}	
	}
}

int main() {
	cin >> M >> N;

	for (int y = 0; y < M; y++) cin >> map[y];

	for (int y = 0; y < M; y++) {
		int direction;
		for (int x = 0; x < N; x++) {
			if (used[y][x] == 1) continue;
			
			if (map[y][x] == '-') direction = 0;
			else direction = 1;

			cnt++;
			dfs(y, x, direction);
		}
	}

	cout << cnt;

	return 0;
}