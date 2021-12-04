// 동철이의 일 분배
#define MAX 16

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
int task[MAX][MAX];
int used[MAX];

long double max_result = 0;
int memo[MAX];

void dfs(int level, long double prob) {
	if (level == N) {
		max_result = max(max_result, prob);
		return;
	}
	
	for (int i = 0; i < N; i++) {
		if (used[i]) continue;
		long double calc_prob = prob * (long double)task[level][i] / 100;
		if (calc_prob > max_result) {
			used[i] = true;
			memo[level] = task[level][i];
			dfs(level + 1, calc_prob);
			used[i] = false;
		}
	}
}

void solve() {
	max_result = 0;
	memset(memo, 0, sizeof(memo));
	dfs(0, 1.0);
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int T; cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N;
		memset(task, 0, sizeof(task));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> task[i][j];
			}
		}
		solve();
		printf("#%d %06lf\n", t + 1, max_result * 100);
	}
}