#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, H, T;

priority_queue<int, vector<int>, less<int>> pq;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> H >> T;

	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		pq.push(a);
	}

	int cnt = 0;
	int flag = 0;
	int h;
	while (1) {
		h = pq.top();

		if (h >= H && h > 1 && T > 0) {
			pq.pop();
			pq.push(h / 2);
			T--;
			cnt++;
		}
		else {
			break;
		}
		
	}

	if (h >= H) {
		cout << "NO\n";
		cout << h << "\n";
	}
	else {
		cout << "YES\n";
		cout << cnt << "\n";
	}
	

	return 0;
}