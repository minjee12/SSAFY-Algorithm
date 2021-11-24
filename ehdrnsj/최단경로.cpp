#include <iostream>
#include <queue>
#include <vector>

#define INF 100000000

using namespace std;

int V, E;
int d[20001];

struct node {
	int n;
	int dist;
};

bool operator<(node back, node front) {
	return front.dist < back.dist;
}

vector<node> alist[20001];
priority_queue<node> pq;
int cnt;

void dijkstra(node start) {
	pq.push(start);
	d[start.n] = start.dist;

	while (!pq.empty()) {
		cnt++;
		node now = pq.top();
		pq.pop();

		if (now.dist > d[now.n]) continue;

		int size = alist[now.n].size();
		for (int i = 0; i < size; i++) {
			node next = alist[now.n][i];
			if (d[next.n] > now.dist + next.dist) {
				d[next.n] = now.dist + next.dist;

				pq.push({next.n, d[next.n]});
			}
		}
	}
}

void input() {
	for (int i = 1; i <= E; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		alist[u].push_back({ v, w });
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> V >> E;
	int start; cin >> start;

	input();

	for (int i = 1; i <= V; i++) {
		d[i] = INF;
	}

	dijkstra({start, 0});

	for (int i = 1; i <= V; i++) {
		if (d[i] == INF) cout << "INF\n";
		else cout << d[i] << "\n";
	}

	return 0;
}