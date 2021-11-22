// 최단 경로
// https://www.acmicpc.net/problem/1753

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX 20001
using namespace std;

int V, E, K;
vector<pair<int, int>> vertex[MAX];
int table[MAX];
bool used[MAX];

void print_weight() {
	for (int i = 1; i <= V; i++) {
		if (table[i] == 1e9) cout << "INF\n";
		else cout << table[i] << "\n";
	}
}

void dijkstra() {
	priority_queue<pair<int, int>> q;
	table[K] = 0;
	q.push({ 0,K });
	while (q.size()) {
		int cur_node = q.top().second;
		q.pop();

		used[cur_node] = true;

		for (int i = 0; i < vertex[cur_node].size(); i++)
		{
			int weight = vertex[cur_node][i].first;
			int next_node = vertex[cur_node][i].second;
			if (table[next_node] > table[cur_node] + weight) {
				table[next_node] = table[cur_node] + weight;
				q.push({ -table[next_node], next_node });
			}
		}
	}
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	cin >> V >> E >> K;
	fill(table + 1, table + V + 1, 1e9);
	table[K] = 0;
	for (int i = 0; i < E; i++) {
		int u, v, w; cin >> u >> v >> w;
		vertex[u].push_back({ w, v });
	}

	dijkstra();
	print_weight();
	return 0;
}