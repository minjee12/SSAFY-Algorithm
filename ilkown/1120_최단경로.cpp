#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int V, E, K;
const int m = 9999999;

struct Node {
	int target;
	int price;
};

bool operator<(Node back, Node front) {
	return front.price < back.price;
}

priority_queue<Node> pq;
vector<vector<Node>> vec(20001);

int result[20001];
int used[20001] = {1};
int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> V >> E;
	cin >> K;

	for (int i = 1; i <= V; i++) {
		result[i] = m;
	}

	for (int i = 0; i < E; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		vec[u].push_back({ v,w });
	}

	result[K] = 0;
	pq.push({ K,0 });

	while (!pq.empty()) {
		Node via = pq.top();
		pq.pop();

		if (used[via.target] == 1) continue;
		used[via.target] = 1;

		int sz = vec[via.target].size();
		for (int i = 0; i < sz; i++) {
			Node target = vec[via.target][i];

			if (result[target.target] > via.price + target.price) {
				result[target.target] = via.price + target.price;
				pq.push({ target.target,result[target.target] });
			}
		}
	}

	for (int i = 1; i <= V; i++) {
		if (result[i] == m) cout << "INF" << endl;
		else cout << result[i] << endl;
	}

	return 0;
}