// 광이삼의 암벽 등반

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int M, N, L;
int ring_cnt = 0;
int board[10][10];

vector<pair<int, int>> rings;
int st_x;
int st_y;
int ed_x;
int ed_y;
int ed_idx;

int used[9]; // 고리 사용 여부
void dfs(int level, int x, int y) {
	// 도착지 인접한 경우
	if (abs(ed_x - x) + abs(ed_y - y) <= L) {
		ring_cnt = min(ring_cnt, level);
		return;
	}
	for (int i = 0; i < rings.size(); i++) {
		if (used[i]) continue;
		if (abs(rings[i].first - x) + abs(rings[i].second - y) <= L) {
			used[i] = true;
			dfs(level + 1, rings[i].first, rings[i].second);
			used[i] = false;
		}
	}
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int T; cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> M >> N >> L;
		memset(board, 0, sizeof(board));
		ring_cnt = 1e6;
		rings.clear();
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
				if (board[i][j] == 1) {
					rings.push_back({ i, j });
				}
				if (board[i][j] == 2) {
					st_x = i;
					st_y = j;
				}
				if (board[i][j] == 3) {
					ed_x = i;
					ed_y = j;
				}
			}
		}
		dfs(0, st_x, st_y);
		cout << "#" << t + 1 << " ";
		if (ring_cnt == 1e6) cout << -1 << "\n";
		else cout << ring_cnt << "\n";
	}
}