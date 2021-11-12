#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, x;
int map[201][201];
vector<int> plan;

bool bfs(int start, int target) {
	int visited[201] = {0,};
	queue<int> q;
	visited[start] = 1;
	q.push(start);
	
	while (!q.empty()) {
		int f = q.front();
		q.pop();

		if (f == target) return true;

		for (int i = 1; i <= n; i++) {
			if (!visited[i] && map[f][i] == 1) {
				visited[i] = 1;
				q.push(i);
			}
		}
	}

	return false;
}

int main() {

	//input
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		cin >> x;
		plan.push_back(x);
	}

	for (int i = 1; i < m; i++) {
		int start = plan[i - 1];
		int target = plan[i];
		bool check = bfs(start, target);
		if (check == false) {
			cout << "NO" << endl;
			exit(0);
		}
	}

	cout << "YES" << endl;

	return 0;
}