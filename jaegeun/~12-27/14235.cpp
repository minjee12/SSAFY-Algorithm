// 크리스마스 선물
// https://www.acmicpc.net/problem/14235

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int N; cin >> N;
	priority_queue<int> pq;
	for (int i = 0; i < N; i++) {
		int a; cin >> a;
		if (a == 0) {
			if (pq.size() == 0) cout << -1 << "\n";
			else {
				cout << pq.top() << "\n";
				pq.pop();
			}
		}
		else {
			for (int j = 0; j < a; j++) {
				int n; cin >> n;
				pq.push(n);
			}
		}
	}
	return 0;
}