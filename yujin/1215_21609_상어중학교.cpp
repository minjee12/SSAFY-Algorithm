#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;

struct info {
	int b_cnt;
	int r_cnt;
	int y;
	int x;
};
bool cmp(info front, info back) {
	if (front.b_cnt == back.b_cnt) {
		if (front.r_cnt == back.r_cnt) {
			if (front.y == back.y) {
				return front.x > back.x;
			}
			return front.y > back.y;
		}
		return front.r_cnt > back.r_cnt;
	}
	return front.b_cnt > back.b_cnt;
}
int n, m, score;
int ty, tx;
int map[21][21];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

bool find_big_block() {
	vector<info> block;
	int visited[21][21] = { 0, };

	//블록그룹찾기
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			if (map[y][x] > 0 && !visited[y][x]) { //일반블록이고, 방문하지 않았다면
				int color = map[y][x];
				queue<pair<int, int> > q;
				q.push({ y, x });
				visited[y][x] = 1;
				int b_cnt = 1;
				int r_cnt = 0;

				//블록묶음
				while (!q.empty()) {
					int yy = q.front().first;
					int xx = q.front().second;
					q.pop();

					for (int i = 0; i < 4; i++) {
						int ny = yy + dy[i];
						int nx = xx + dx[i];

						if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
						if (map[ny][nx] == -2) continue;
						if (visited[ny][nx] == 1) continue;
						if (map[ny][nx] == -1) continue;
						if (map[ny][nx] == color) { //기준색과 같은 일반블록
							b_cnt++;
							visited[ny][nx] = 1;
							q.push({ ny, nx });
						}
						if (map[ny][nx] == 0) { //무지개블록
							r_cnt++;
							b_cnt++;
							visited[ny][nx] = 1;
							q.push({ ny, nx });
						}

					}
				}

				//블록묶음이 두개이상이면 블록그룹에 등록
				if (b_cnt >= 2) {
					block.push_back({ b_cnt, r_cnt, y, x });
				}
				//무지개였던곳 visited[][] = 0
				for (int i = 1; i <= n; i++) {
					for (int j = 1; j <= n; j++) {
						if (map[i][j] == 0) visited[i][j] = 0;
					}
				}
			}
		}
	}

	if (block.size() == 0) return false;

	//블록그룹 정렬
	sort(block.begin(), block.end(), cmp);

	//크기 큰 블록 : 타겟 x, y
	ty = block[0].y;
	tx = block[0].x;

	return true;
}

void remove_big_block() {
	int visited[21][21] = { 0, };
	int color = map[ty][tx];
	queue<pair<int, int> > q;
	q.push({ ty, tx });
	map[ty][tx] = -2;
	visited[ty][tx] = 1;
	int cnt = 1;

	//블록묶음
	while (!q.empty()) {
		int yy = q.front().first;
		int xx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = yy + dy[i];
			int nx = xx + dx[i];

			if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
			if (visited[ny][nx] == 1) continue;
			if (map[ny][nx] == -1) continue; //검은블록
			if (map[ny][nx] == -2) continue; //빈칸
			if (map[ny][nx] == color || map[ny][nx] == 0) {
				cnt++;
				map[ny][nx] = -2;
				visited[ny][nx] = 1;
				q.push({ ny, nx });
			}
		}
	}

	score += cnt * cnt;
}

void gravity() {
	for (int x = 1; x <= n; x++) {
		for (int y = n - 1; y >= 1; y--) {
			if (map[y][x] == -2) continue; //빈칸이면 무시
			if (map[y][x] != -1) { //검은블록이 아니면
				int val = map[y][x];
				for (int i = y + 1; i <= n; i++) {
					if (map[i][x] != -2) {
						map[y][x] = -2;
						map[i - 1][x] = val;
						break;
					}
					else if (map[i][x] == -2 && i == n) {
						map[y][x] = -2;
						map[i][x] = val;
					}
				}
			}
		}
	}
}

void rotation() {
	int tmp[21][21] = { 0, };
	for (int x = n; x >= 1; x--) {
		for (int y = 1; y <= n; y++) {
			tmp[n + 1 - x][y] = map[y][x];
		}
	}
	memcpy(map, tmp, sizeof(map));
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	while (1) {
		bool check = find_big_block();
		if (check == false) break;
		remove_big_block();
		gravity();
		rotation();
		gravity();
	}

	cout << score << "\n";

	return 0;
}