// 회전하는 큐
// https://www.acmicpc.net/problem/1021
#include <iostream>
#include <queue>

using namespace std;

void rotate_queue(deque<int>& queue, int cnt, bool is_left) {
	while (cnt != 0) {
		if (is_left) {
			queue.push_front(queue.back());
			queue.pop_back();
		}
		else {
			queue.push_back(queue.front());
			queue.pop_front();
		}
		cnt--;
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);

	int n, m; cin >> n >> m;
	deque<int> q(n);
	for (int i = 0; i < n; i++) q[i] = i + 1; // deque 초기화

	int opt_cnt = 0;
#ifdef _DEBUG
	for (auto x : q)
		cout << x << " ";
	cout << "\n";
#endif
	for (int i = 0; i < m; i++) {
		int target; cin >> target; // 뺄 값
		int idx; // 뺄 값의 인덱스
		for (idx = 0; idx < q.size(); idx++) {
			if (q[idx] == target) break;
		}
		if (idx <= q.size() / 2) { // 절반보다 작으면
			rotate_queue(q, idx, false); // target이 맨 앞으로 옴
			opt_cnt += idx;
		}
		else {
			rotate_queue(q, q.size() - idx, true);
			opt_cnt += q.size() - idx;
		}
#ifdef _DEBUG
		for (auto x : q)
			cout << x << " ";
		cout << "\n";
#endif
		q.pop_front(); // 큐 pop
	}
	cout << opt_cnt << "\n";
	return 0;
}