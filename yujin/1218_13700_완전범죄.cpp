#include <iostream>
#include <queue>
using namespace std;

int police[50001];
int visited[100001];
int n, s, d, f, b, k;
queue<pair<int, int> > q; //현재위치, 버튼횟수

bool check_police(int now) {
	for (int i = 0; i < k; i++) {
		if (police[i] == now) return false; //경찰서로가면
	}
	return true;
}

int bfs() {
	q.push({ s, 0 });
	visited[s] = 1;

	while (!q.empty()) {
		int now = q.front().first;
		int cnt = q.front().second;
		q.pop();

		//현재 위치가 대도의 집이면
		if (now == d) return cnt;
		
		//앞으로 가는 경우
		int nnow = now + f;
		//이동할 위치가 경찰서면 continue
		if (check_police(nnow)) {
			if (0 < nnow && nnow <= 100000) {
				if (visited[nnow] != 1) {
					visited[nnow] = 1;
					q.push({ nnow, cnt + 1 });
				}
			}
		}
		
		//뒤로 가는 경우
		nnow = now - b;
		//이동할 위치가 경찰서면 continue
		if (check_police(nnow)) {
			if (0 < nnow && nnow <= 100000) {
				if (visited[nnow] != 1) {
					visited[nnow] = 1;
					q.push({ nnow, cnt + 1 });
				}
			}
		}
	}

	return -1;
}

int main() {

	cin >> n >> s >> d >> f >> b >> k;
	for (int i = 0; i < k; i++) {
		cin >> police[i];
	}

	int res = bfs();
	if (res == -1) cout << "BUG FOUND\n";
	else cout << res << "\n";

	return 0;
}