#include <iostream>
#include <queue>
#include <vector>
using namespace std;

priority_queue<int, vector<int>, less<int>> pq;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		if (a == 0) {
			if (pq.empty()) cout << -1 << "\n";
			else {
				cout << pq.top() << "\n";
				pq.pop();
			}
		}
		else {
			for (int j = 0; j < a; j++) {
				int num;
				cin >> num;
				pq.push(num);
			}
		}
	}

	return 0;
}