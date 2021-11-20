#include<iostream>
#include<queue>
#include<vector>
using namespace std;

vector<int> v[50];
bool c[50];
int N, M;

void bfs(int start) {
	queue<int> q;
	q.push(start);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		c[x] = true;
		for (int i = 0; i < v[x].size(); i++) {
			if (c[v[x][i]] == false) q.push(v[x][i]);
		}
	}
}

int main() {
	int cnt = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		if (a != -1) v[a].push_back(i);
	}

	cin >> M;
	bfs(M);
	for (int i = 0; i < N; i++) {
		if (c[i] == false) {
			int num = 0;
			for (int j = 0; j < v[i].size(); j++) {
				if (c[v[i][j]] == false) break;
				num++;
			}
			if (v[i].size() == num) cnt++;
		}
	}

	cout << cnt;
	return 0;
}