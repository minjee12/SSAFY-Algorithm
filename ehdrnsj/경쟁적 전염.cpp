#include <iostream>
#include <queue>

#define MAX 201

using namespace std;

int N, K;
int S, Y, X;

int direct[4][2] = {
	-1, 0, 0, 1, 1, 0, 0, -1
};
int map[MAX][MAX];

struct node{
	int virus;
	int y, x;
	int time;
};
priority_queue<node> pq;

bool operator<(node back, node front) {
	return front.virus < back.virus;
}

void bfs() {
	for (int i = 0; i < S; i++) {
		queue<node> q;
		
		while (!pq.empty()) {
			q.push(pq.top());
			pq.pop();
		}

		while (!q.empty()) {
			node now = q.front();
			q.pop();

			for (int t = 0; t < 4; t++) {
				int dy = now.y + direct[t][0];
				int dx = now.x + direct[t][1];

				if (dy < 1 || dx < 1 || dy > N || dx > N) continue;
				if (map[dy][dx] != 0) continue;

				map[dy][dx] = now.virus;

				pq.push({ now.virus, dy, dx, now.time + 1 });
			}
		}
	}
}

void input() {
	cin >> N >> K;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> map[y][x];
			if (map[y][x] != 0) {
				pq.push({ map[y][x], y, x, 0 });
			}
		}
	}

	cin >> S >> Y >> X;
}

int main() {
	input();
	bfs();

	cout << map[Y][X];

	return 0;
}