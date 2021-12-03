#include <iostream>

#define MAX 100001

using namespace std;

int N;

int level[MAX];
int who_is_parent[MAX];
int num_of_children[MAX];

int answer_idx;
int answer_list[MAX];

void check_dfs(int lv, int now, int parent) {
	if (lv != level[now]) {
		cout << 0;
		exit(0);
	}
	if (parent != who_is_parent[now]) {
		cout << 0;
		exit(0);
	}

	for (int n = 0; n < num_of_children[now]; n++) { 
		check_dfs(lv + 1, answer_list[answer_idx++], now);
	}
}

int main() {
	cin >> N;

	level[1] = 0;
	who_is_parent[1] = 0;

	for (int i = 1; i < N; i++) {
		int parent, child;
		cin >> parent >> child;
		
		level[child] = level[parent] + 1;
		who_is_parent[child] = parent;
		num_of_children[parent]++;
	}

	for (int i = 0; i < N; i++) {
		int answer;
		cin >> answer;
		answer_list[i] = answer;
	}

	check_dfs(0, answer_list[answer_idx++], 0);
	cout << 1;

	return 0;
}