// 센티와 마법의 뿅망치
// https://www.acmicpc.net/problem/19638

#include <iostream>
#include <queue>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	priority_queue<int> q;

	int N, Hc, T; cin >> N >> Hc >> T;
	int H;
	for (int i = 0; i < N; i++) {
		cin >> H;
		q.push(H);
	}

	int cnt = 0;
	while (true) {
		if (cnt >= T) break;
		int Ht = q.top();
		if (q.top() < Hc) break;
		if (Ht != 1) {
			q.pop();
			q.push(Ht / 2);
		}
		cnt++;
	}
	if (cnt >= T && q.top() >= Hc) {
		cout << "NO\n";
		cout << q.top();
	}
	else {
		cout << "YES\n";
		cout << cnt;
	}
	return 0;
}
