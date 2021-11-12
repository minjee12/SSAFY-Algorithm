#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

int parent[10001];
int depth[10001];

void handle_depth(int child , int cur, int level) {
	if (parent[cur] == 0) {
		depth[child] = level;
		return;
	}
	handle_depth(child, parent[cur], level + 1);
}

int find_parent(int a, int b) {
	while (parent[a] != parent[b]) {
		a = parent[a];
		b = parent[b];
	}

	return parent[a];
}

int main() {

	int tc;

	cin >> tc;

	while (tc--) {
		int N;
		cin >> N;

		memset(parent, 0, sizeof(parent));
		memset(depth, 0, sizeof(depth));

		for (int i = 0; i < N - 1; i++) {
			int a, b;
			cin >> a >> b;

			parent[b] = a;
		}
		
		int parent_a, parent_b;

		cin >> parent_a >> parent_b;

		handle_depth(parent_a, parent_a, 0);
		handle_depth(parent_b, parent_b, 0);

		int level_a = depth[parent_a];
		int level_b = depth[parent_b];

		if (level_a == level_b) {
			if (parent[parent_a] == parent[parent_b]) cout << parent[parent_a] << endl;
			else {
				cout << find_parent(parent_a, parent_b) << endl;
			}
		}
		else if (level_a < level_b) {
			while (level_a != level_b) {
				parent_b = parent[parent_b];
				level_b--;
			}
			if (parent_a == parent_b) cout << parent_a << endl;
			else
				cout << find_parent(parent_a, parent_b) << endl;
		}
		else if (level_a > level_b) {
			while (level_a != level_b) {
				parent_a = parent[parent_a];
				level_a--;
			}
			if (parent_a == parent_b) cout << parent_a << endl;
			else
				cout << find_parent(parent_a, parent_b) << endl;
		}
	
	}

	return 0;
}
