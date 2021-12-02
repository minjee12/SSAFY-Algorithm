// BFS 스페셜 저지
// https://www.acmicpc.net/problem/16940

#define MAX 100001

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, idx = 0;
int seq[MAX];
int order[MAX];
bool used[MAX];

vector<int> tree[MAX];

bool compair(int a, int b) {
	return order[a] < order[b];
}

void bfs() {
	queue<int> q;
	q.push(1);
	used[1] = true;
	while (q.size())
	{
		int cx = q.front();
		q.pop();
		if (cx != seq[idx++]) {
			cout << 0;
			exit(0);
		}
		for (auto x : tree[cx]) {
			if (used[x]) continue;
			used[x] = true;
			q.push(x);
		}
	}
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int a, b; cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
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
		sort(tree[i].begin(), tree[i].end(), compair);
	}
	bfs();
	cout << 1;
	return 0;
}
