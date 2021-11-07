// 풍선 터뜨리기
// https://www.acmicpc.net/problem/2346

#include <iostream>
#include <queue>

using namespace std;

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);

	int N; cin >> N;
	// 풍선 번호, 입력 숫자
	deque<pair<int, int>> d;
	for (int i = 1; i <= N; i++) {
		int num; cin >> num;
		d.push_back({ i, num });
	}

	while (d.size()) {
		cout << d.front().first << " ";
		int next = d.front().second;

		d.pop_front();
		if (next > 0 && d.size()) {
			for (int i = 0; i < next - 1; i++) {
				d.push_back(d.front());
				d.pop_front();
			}
			continue;
		}
		if (d.size()) {
			for (int i = 0; i > next; i--) {
				d.push_front(d.back());
				d.pop_back();
			}
		}
	}
	return 0;
}