#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define max_ 100001

int n;
int parent[100001] = {};
vector<int> vec[100001];
int visited[100001] = {};
int root = 1;
int order[100001] = {};
int dfs_order[100001] = {};
int cur_idx = 0;
int ans = 1;

int cmp(int front, int back) {
	return dfs_order[front] < dfs_order[back];
}

void dfs(int cur) {

	if (cur != order[cur_idx++]) {
		ans = 0;
		return;
	}

	int sz = vec[cur].size();
	for (int i = 0; i < sz; i++) {
		int next = vec[cur][i];

		if (visited[next] == 1) continue;
		visited[next] = 1;
		dfs(next);

	}

}
	

int main() {

	ios::sync_with_stdio(false);
	cin.tie(null);
	cout.tie(null);

	cin >> n;

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	for (int i = 0; i < n; i++) {
		cin >> order[i];
		dfs_order[order[i]] = i + 1;
	}

	for (int i = 1; i <= n; i++) {
		sort(vec[i].begin(), vec[i].end(), cmp);
	}
	visited[root] = 1;

	dfs(root);

	cout << ans << "\n";

	return 0;
}