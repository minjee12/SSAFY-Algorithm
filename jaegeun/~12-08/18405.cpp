// 경쟁적 전염
// https://www.acmicpc.net/problem/18405

#define MAX 200
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

int N, K;
int S, X, Y;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
int examiner[MAX][MAX];
int is_add[1001]; // virus_num에 추가 했는지 여부
vector<int> virus_num;
deque<pair<int, int>> virus_pos[1001]; // 바이러스 위치

void spread() {
	for (int v = 0; v < virus_num.size(); v++) {
		int cur_v = virus_num[v];
		int cur_size = virus_pos[cur_v].size();
		for (int i = 0; i < cur_size; i++) {
			int cx = virus_pos[cur_v].front().first;
			int cy = virus_pos[cur_v].front().second;

			for (int d = 0; d < 4; d++) {
				int nx = cx + dx[d];
				int ny = cy + dy[d];
				if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
				if (examiner[nx][ny]) continue;
				examiner[nx][ny] = cur_v;
				virus_pos[cur_v].push_back({ nx, ny });
			}
			virus_pos[cur_v].pop_front();
		}
	}
}

void solve() {
	for (int i = 0; i < S; i++) {
		spread();
		if (examiner[X - 1][Y - 1]) {
			cout << examiner[X - 1][Y - 1];
			exit(0);
		}
	}
	cout << examiner[X - 1][Y - 1];
}
int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> examiner[i][j];
			if (examiner[i][j] > 0) {
				int cur_type = examiner[i][j];
				virus_pos[cur_type].push_back({ i, j });
				if (!is_add[cur_type]) {
					is_add[cur_type] = true;
					virus_num.push_back(cur_type);
				}
			}
		}
	}
	cin >> S >> X >> Y;
	sort(virus_num.begin(), virus_num.end());
	solve();
	return 0;
}
