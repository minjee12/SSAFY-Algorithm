// 여행 가자
// https://www.acmicpc.net/problem/1976

#include <iostream>
#define MAX 200

int N, M;

int parent[MAX];
using namespace std;

int find_parent(int A) {
	if (parent[A] == 0) return A;
	return parent[A] = find_parent(parent[A]);
}

void make_union(int A, int B) {
	int pA = find_parent(A);
	int pB = find_parent(B);

	if (pA != pB) {
		parent[pB] = pA;
	}
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> N >> M;
	int c;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> c;
			if (c) {
				make_union(i, j);
			}
		}
	}

	int st = -1;
	for (int i = 0; i < M; i++) {
		cin >> c;
		c--;
		if (st == -1) {
			st = find_parent(c);
			continue;
		}
		if (st != find_parent(c)) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";
	return 0;
}