#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int root = 1;
int order[100001] = {};
int visited[100001] = {};
vector<int>vec[100001];
int bfs_order[100001] = {};
int cur_idx = 0;
int ans = 1;

int cmp(int front, int back) {
	return bfs_order[front] < bfs_order[back];
}
void BFS() {
	queue<int> que;
	que.push(root);

	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		if (cur != order[cur_idx++]) {
			ans = 0;
			break;
		}

		int sz = vec[cur].size();

		for (int i = 0; i < sz; i++) {
			int next = vec[cur][i];
			if (visited[next] == 1) continue;
			visited[next] = 1;
			que.push(next);
		}
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	
	for (int i = 0; i < N; i++) {
		cin >> order[i];
		bfs_order[order[i]] = i + 1;
	}
	visited[root] = 1;

	for (int i = 1; i <= N; i++) {
		sort(vec[i].begin(), vec[i].end(), cmp);
	}

	BFS();

	cout << ans << endl;

	return 0;
}