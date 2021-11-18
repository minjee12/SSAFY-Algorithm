#include <iostream>
#include <queue>
using namespace std;

int N, D;
int map[51][51];
int sum[51];
int del[51];
int root;
int cnt;

void check_brother(int target) {
	for (int y = 1; y <= N; y++) {
		if (map[y][target] == 1) {
			if (sum[y] == target) {
				cnt++;
			}
			return;
		}
	}
}

void delete_tree(int start) {
	queue<int> q;
	q.push(start);
	del[start] = 1;

	while (!q.empty()) {
		int y = q.front();
		q.pop();
		if (sum[y] == 0) continue; // y가 리프인 경우

		for (int x = 1; x <= N; x++) {
			if (map[y][x] == 0) continue;
			if (del[x] == 1) continue;
			del[x] = 1;

			q.push(x);
		}
	}
}

int main() {
	cin >> N;

	for (int x = 1; x <= N; x++) {
		int y; cin >> y; y++;
		if (y != 0) {
			map[y][x] = 1;
			sum[y] += x;
		}
		else {
			root = x;
		}
	}

	cin >> D; D++;
	if (D == root) cout << 0;
	else {
		check_brother(D);
		delete_tree(D);
		for (int x = 1; x <= N; x++) {
			if (del[x] != 1 && sum[x] == 0) cnt++;
		}
		cout << cnt;
	}

	return 0;
}