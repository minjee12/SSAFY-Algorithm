// 지름길
// https://www.acmicpc.net/problem/1446

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX 10001

using namespace std;

int N, D;
vector<pair<int, int>> node[MAX];
int table[MAX];
bool visited[MAX];

void dik() {
	priority_queue<pair<int, int>> q;
	q.push({ 0, 0 });

	while (q.size()) {
		int cur = q.top().second;
		int cur_w = -q.top().first;
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
	cin >> N >> D;
	fill(table + 1, table + MAX - 1, 1e9);
	for (int i = 0; i <= D; i++) {
		if (i < 10000) node[i].push_back({ 1, i + 1 });
	}

	for (int i = 0; i < N; i++) {
		int st, ed, len; cin >> st >> ed >> len;
		node[st].push_back({ len, ed });
	}
	dik();
	for (int i = 0; i <= D; i++) {
		table[D] = min(table[D], D - i + table[i]);
	}
	cout << table[D];
	return 0;
}
