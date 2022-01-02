#define MAX 20
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int dx[] = { 1, 1, -1, -1 };
int dy[] = { -1, 1, 1, -1 };

int N;
int board[MAX][MAX];

bool get_enable(int sx, int sy, int left, int right) {
	bool visit[101] = { false, };
	visit[board[sx][sy]] = true;
	int cnt[4] = { left,right, left,right };
	int d = 0;
	int step = 0;
	int cx = sx;
	int cy = sy;
	while (true) {
		if (step == cnt[d]) {
			d++; step = 0;
		}
		cx = cx + dx[d];
		cy = cy + dy[d];
		if (cx >= N || cx < 0 || cy < 0 || cy >= N) return false;
		if (cx == sx && cy == sy) break;
		if (visit[board[cx][cy]]) {
			return false;
		}
		visit[board[cx][cy]] = true;
		step++;
	}
	return true;
}

int check(int st_x, int st_y) {
	int enable_left = st_y;
	int enable_right = N - st_x - 1;
	int local_visit_num = -1;
	for (int i = 1; i <= enable_left; i++) {
		for (int j = 1; j <= enable_right; j++) {
			bool result = get_enable(st_x, st_y, i, j);
			if (result) {
				local_visit_num = max(local_visit_num, (i + j) * 2);
			}
		}
	}
	return local_visit_num;
}

void solve() {
	memset(board, 0, sizeof(board));
	int max_score = -1;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == 0 && j == 0) continue;
			if (i == 0 && j == N - 1) continue;
			if (i == N - 1 && j == 0) continue;
			if (i == N - 1 && j == N - 1) continue;
			int score = check(i, j);
			max_score = max(max_score, score);
		}
	}
	cout << max_score << "\n";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int T; cin >> T;
	for (int i = 0; i < T; i++) {
		cout << "#" << i + 1 << " ";
		solve();
	}
}
