#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int N, D;

struct Node {
	int  end;
	int cost;
};


int main() {

	int result[10001] = {};
	vector<Node> vec[10001];

	cin >> N >> D;

	for (int i = 0; i < N; i++) {
		int u, v, w;

		cin >> u >> v >> w;

		if (v - u <= w || v > D) continue;

		vec[u].push_back({ v,w });
	}

	for (int i = 0; i <= D; i++) result[i] = i;


	int chk = -1;
	for (int i = 0; i <= D; i++) {

		if (i > 0) chk = result[i - 1];
		result[i] = min(result[i], chk + 1);

		int sz = vec[i].size();

		for (int j = 0; j < sz; j++) {
			Node Next = vec[i][j];

			if (result[Next.end] > Next.cost + result[i]) {
				result[Next.end] = Next.cost + result[i];
			}

		}

	}

	cout << result[D] << endl;
	

	return 0;
}