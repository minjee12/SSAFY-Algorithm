#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

int N, M;
int arr[50][50];
bool c[50][50];
int cnt[50][50];
typedef struct {
	int y, x;
} Dir;

Dir d[8] = { {-1, -1},{-1, 1}, {1, -1}, {1, 1},{-1, 0},{0, 1},{1, 0},{0, -1} };

int bfs(int y, int x) {
	queue<Dir> q;
	q.push({ y, x });
	c[y][x] = true;
	while (!q.empty()) {
		Dir s = q.front();
		q.pop();
		for (int i = 0; i < 8; i++) {
			int ny = s.y + d[i].y;
			int nx = s.x + d[i].x;
			if (!c[ny][nx] && ny >= 0 && nx >= 0 && ny < N && nx < M) {
				q.push({ ny, nx });
				c[ny][nx] = true;
				cnt[ny][nx] = cnt[s.y][s.x] + 1;
				if (arr[ny][nx] == 1) return cnt[ny][nx];
			}

		}
	}
}

int main() {
	int maxi = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] == 0) {
				int a = bfs(i, j);
				maxi = max(a, maxi);
				memset(c, 0, sizeof(c));
				memset(cnt, 0, sizeof(cnt));
			}
		}
	}
	cout << maxi;

	return 0;
}