// 트리
// https://www.acmicpc.net/problem/1068

#include <iostream>
#include <vector>
#define MAX 50
using namespace std;

int N;
int r; // 루트
int cnt = 0; // 리프 개수
int parent[MAX];
vector<int> child[MAX];
vector<int> new_child[MAX];

vector<int> removed_node;

void rm_node(int node) {
	if (child[node].size() == 0) {
		removed_node.push_back(node);
		return;
	}
	for (int i = 0; i < child[node].size(); i++) {
		rm_node(child[node][i]);
	}
	removed_node.push_back(node);
}

void find_leaf(int node) {
	if (new_child[node].size() == 0) {
		cnt++;
		return;
	}
	for (int i = 0; i < new_child[node].size(); i++) {
		find_leaf(new_child[node][i]);
	}
}

bool is_removed(int node) {
	for (int i = 0; i < removed_node.size(); i++) {
		if (removed_node[i] == node) return true;
	}
	return false;
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> parent[i];
		if (parent[i] == -1) r = i;
	}

	// 트리 생성
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j)continue;
			if (i == parent[j]) {
				child[i].push_back(j);
			}
		}
	}

	int num; cin >> num;
	if (num == r) {
		cout << 0;
		return 0;
	}
	rm_node(num); // 노드 삭제

	// 새로운 트리 생성
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j)continue;
			if (is_removed(j)) continue;
			if (i == parent[j]) {
				new_child[i].push_back(j);
			}
		}
	}

	find_leaf(r);
	cout << cnt;
	return 0;
}