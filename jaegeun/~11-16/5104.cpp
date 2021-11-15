// 스타트링크
// https://www.acmicpc.net/problem/5014

#include <iostream>
#include <queue>

using namespace std;

int F, G, S, U, D;
int visited[1000001];

int bfs() {
	deque<int> q;

	q.push_back(S);
	visited[S] = 1;
	while (q.size()) {
		int cur = q.front();
		q.pop_front();

		if (cur + U == G) return visited[cur];
		if (cur - D == G) return visited[cur];

		if (cur + U <= F && !visited[cur + U]) {
			q.push_back(cur + U);
			visited[cur + U] = visited[cur] + 1;
		}
		if (cur - D >= 1 && !visited[cur - D]) {
			q.push_back(cur - D);
			visited[cur - D] = visited[cur] + 1;
		}
	}
	return -1;
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> F >> S >> G >> U >> D;

	if (S == G) {
		cout << 0;
		return 0;
	}
	int result = bfs();
	
	if (result == -1) cout << "use the stairs";
	else cout << result;
	return 0;
}