#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <algorithm>
using namespace std;
#define MAX 21

int N, M;
int map[MAX][MAX];
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
int visited[MAX][MAX] = {};

struct Block {
	int y, x;
	int rainbow_block = 0;
	int block[MAX][MAX] = {};
	int sz = 0;
};

Block b_info;

int isInside(int y, int x) {
	if (y<0 || y>=N || x<0 || x>=N) return 0;
	return 1;
}

void gravity() {

	for (int x = 0; x < N; x++) {
		for (int y = N - 1 ; y > 0; y--) {
			if (map[y][x] == -2) {
				for (int i = y - 1; i >= 0; i--) {
					if (map[i][x] == -1) break;
					if (map[i][x] != -1 && map[i][x] != -2) {
						map[y][x] = map[i][x];
						map[i][x] = -2;
						break;
					}
				}
			}
		}
	}

}


void rotate_90() {
	int temp[MAX][MAX] = {};

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			temp[N - x - 1][y] = map[y][x];
		}
	}
	memcpy(map, temp, sizeof(temp));
}

struct Node {
	int y, x;
};

void bfs(int y, int x) {
	queue<Node> que;
	que.push({ y,x });
	visited[y][x] = 1;

	int temp[MAX][MAX] = {};
	int r_sz = 0;
	int b_sz = 1;
	int start_y = y;
	int start_x = x;

	int color = map[y][x];
	temp[y][x] = 1;

	while (!que.empty()) {
		y = que.front().y;
		x = que.front().x;
		que.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];

			if (!isInside(ny, nx) || visited[ny][nx] != 0 || map[ny][nx] == -1 || map[ny][nx] == -2) continue;
			if (map[ny][nx] == color || map[ny][nx] == 0) {
				if (map[ny][nx] == 0) r_sz++;
				b_sz++;
				visited[ny][nx] = 1;
				temp[ny][nx] = 1;
				que.push({ ny,nx });
			}
		}
	}

	if (b_info.sz < b_sz) {
		b_info.sz = b_sz;
		memcpy(b_info.block, temp, sizeof(temp));
		b_info.rainbow_block = r_sz;
		b_info.y = start_y;
		b_info.x = start_x;
	}
	else if (b_info.sz == b_sz) {
		if (b_info.rainbow_block < r_sz) {
			b_info.sz = b_sz;
			memcpy(b_info.block, temp, sizeof(temp));
			b_info.rainbow_block = r_sz;
			b_info.y = start_y;
			b_info.x = start_x;
		}
		else if (b_info.rainbow_block == r_sz) {
			if (b_info.y < start_y) {
				b_info.sz = b_sz;
				memcpy(b_info.block, temp, sizeof(temp));
				b_info.rainbow_block = r_sz;
				b_info.y = start_y;
				b_info.x = start_x;
			}
			else if (b_info.y == start_y) {
				if (b_info.x < start_x) {
					b_info.sz = b_sz;
					memcpy(b_info.block, temp, sizeof(temp));
					b_info.rainbow_block = r_sz;
					b_info.y = start_y;
					b_info.x = start_x;
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 0) {
				visited[i][j] = 0;
			}
		}
	}
}


int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int ans = 0;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	while (1) {

		memset(visited, 0, sizeof(visited));
		b_info.sz = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] > 0 && visited[i][j] == 0) {
					bfs(i, j);
				}
			}
		}

		if (b_info.sz <= 1) break;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (b_info.block[i][j] == 1) {
					map[i][j] = -2;
				}
			}
		}

		ans += b_info.sz*b_info.sz;

		gravity();

		rotate_90();

		gravity();
	}

	cout << ans << "\n";

	return 0;
}