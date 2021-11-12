#include <iostream>
#include <vector>
using namespace std;

int t, n;
int node1, node2;
int res;

int main() {
	cin >> t;
	for (int test_case = 1; test_case <= t; test_case++) {
		//input
		cin >> n;
		vector<int> child[10001];
		for (int i = 1; i < n; i++) {
			int p = 0, c = 0;
			cin >> p >> c;
			child[c].push_back(p);
		}
		cin >> node1 >> node2;

		//첫번째 노드와 그 부모들 visited에 체크
		int visited[10001] = { 0, };
		int start = node1;
		visited[start] = 1;
		while (1) {
			if (child[start].empty()) break;
			visited[child[start][0]] = 1;
			start = child[start][0];
		}

		//두번째 노드와 그 부모들중에 visited == 1이면 정답
		start = node2;
		if (visited[start] == 1) {
			cout << res << "\n";
			continue;
		}
		while (1) {
			if (child[start].empty()) break;
			if (visited[child[start][0]] == 1) {
				res = child[start][0];
				break;
			}
			start = child[start][0];
		}

		cout << res << "\n";
	}

	return 0;
}