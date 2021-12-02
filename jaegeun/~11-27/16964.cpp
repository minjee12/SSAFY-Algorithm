// DFS 스페셜 저지
// https://www.acmicpc.net/problem/16964

#define MAX 100001

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int idx = 0;
bool error;
vector<int> tree[MAX];
int seq[MAX];
bool used[MAX];
int order[MAX];

bool compare(int a, int b) {
	return order[a] < order[b];
}

void dfs(int x) {
	if (x != seq[idx++]) {
		cout << 0 << "\n";
		exit(0);
	}
	for(int i = 0; i < tree[x].size(); i++){
		int nx = tree[x][i];
		if (used[nx]) continue;
		used[nx] = true;
		dfs(nx);
	}
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int p, c; cin >> p >> c;
		tree[p].push_back(c);
		tree[c].push_back(p);
	}
	
	for (int i = 0; i < N; i++) {
		cin >> seq[i];
		order[seq[i]] = i + 1;
	}

	if (seq[0] != 1) {
		cout << 0;
		return 0;
	}

	for (int i = 1; i <= N; i++) {
		sort(tree[i].begin(), tree[i].end(), compare);
	}
	
	used[1] = true;
	dfs(1);
	cout << 1 << "\n";
	return 0;
}