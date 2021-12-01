// 편의점
// https://www.acmicpc.net/problem/14221

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

#define MAX 5001

using namespace std;

int N, M, P, Q;
vector<pair<int, int>> node[MAX];
int table[MAX]; // 가중치
int home[MAX];
int conb[MAX];
bool is_home[MAX];
bool is_conb[MAX];

pair<int, int> dik(int st) {
	priority_queue<pair<int, int>> q;
	fill(table, table + MAX, 1e9);
	table[st] = 0;
	q.push({ 0, st });

	while (q.size()) {
		int cur = q.top().second;
		int cur_w = -q.top().first;
		if (is_home[cur]) return { cur, cur_w };
		q.pop();
		for (auto x : node[cur]) {
			int nx = x.second;
			int w = x.first;
			if (table[nx] > table[cur] + w) {
				table[nx] = table[cur] + w;
				q.push({ -table[nx], nx });
			}
		}
	}
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int st, ed, len; cin >> st >> ed >> len;
		node[st].push_back({ len, ed });
		node[ed].push_back({ len, st });
	}
	cin >> P >> Q;
	for (int i = 0; i < P; i++) {
		cin >> home[i];
		is_home[home[i]] = true;
	}
	for (int i = 0; i < Q; i++) {
		cin >> conb[i];
		is_conb[conb[i]] = true;
	}

	int min_dist = 1e9;
	int min_idx = 1e9;
	for (int i = 0; i < Q; i++) {
		auto result = dik(conb[i]);
		int dist = result.second;
		int home_num = result.first;
		if (min_dist > dist) {
			min_idx = home_num;
			min_dist = dist;
		}
		else if (min_dist == dist && min_idx > home_num) {
			min_idx = home_num;
		}
	}
	cout << min_idx;
	return 0;
}