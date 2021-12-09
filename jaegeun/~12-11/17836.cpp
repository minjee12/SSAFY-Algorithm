// 공주님을 구해라!
// https://www.acmicpc.net/problem/17836


#define MAX 100

#include <iostream>
#include <queue>

using namespace std;

int N, M, T;

int bram_x = -1;
int bram_y = -1;
bool get_bram = false;
int get_bram_time = -1;

int castle[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

typedef struct {
	int x, y;
	int time;
}info;

int solve() {
	queue<info> q;
	q.push({ 0, 0, 0 });
	

	while (q.size()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int ct = q.front().time;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (visited[nx][ny]) continue;
			if (castle[nx][ny] == 1) continue;
			if (castle[nx][ny] == 2) {
				get_bram = true;
				get_bram_time = ct + 1;
			}
			if (nx == N - 1 && ny == M - 1) return ct + 1;
			visited[nx][ny] = true;
			q.push({ nx, ny, ct + 1 });
		}
	}
	return -1;
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M >> T;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> castle[i][j];
			if (castle[i][j] == 2) {
				bram_x = i;
				bram_y = j;
			}
		}
	}
	int t = solve();
	if (get_bram) {
		int bram_t = (N - bram_x - 1) + (M - bram_y - 1) + get_bram_time;
		if (t != -1) {
			int min_time = min(bram_t, t);
			if (min_time <= T) cout << min_time;
			else cout << "Fail";
		}
		if (t == -1) {
			if (bram_t <= T) cout << bram_t;
			else cout << "Fail";
		}
	}
	else {
		if (t == -1) {
			cout << "Fail";
		}
		else {
			if (t <= T) cout << t;
			else cout << "Fail";
		}
	}
	return 0;
}
