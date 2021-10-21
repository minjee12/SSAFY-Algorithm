// 네트워크 연결
// https://www.acmicpc.net/problem/1922

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 1001

int N, M;

int parent[MAX];

int find_parent(int child) {
	if (!parent[child]) return child;
	else return parent[child] = find_parent(parent[child]);
}

bool set_union(int a, int b) {
	int a_p = find_parent(a);
	int b_p = find_parent(b);
	if (a_p == b_p) return false;
	
	parent[b_p] = a_p;
	return true;
}

bool compair(pair<int, pair<int, int>> f, pair<int, pair<int, int>> b) {
	return f.first < b.first;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M; 
	vector<pair<int, pair<int, int>>> vect(M);
	
	for (int i = 0; i < M; i++) {
		int cost, a, b; cin >> a >> b >> cost;
		vect[i] = { cost, {a, b} };
	}
	sort(vect.begin(), vect.end(), compair);

	int cnt = 0;
	int total_cost = 0;
	for (int i = 0; i < M; i++) {
		if (cnt == N - 1) break;
		if (set_union(vect[i].second.first, vect[i].second.second)) {
			total_cost += vect[i].first;
			cnt++;
		}
	}
	cout << total_cost;
	return 0;
}