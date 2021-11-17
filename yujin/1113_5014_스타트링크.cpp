#include <iostream>
#include <queue>
using namespace std;

int f, s, g, u, d;

int bfs() {
	queue<pair<int, int> > q; //현재 위치, 몇번 이동했는지
	int visited[1000001] = { 0, };
	
	visited[s] = 1;
	q.push({s, 0});
	
	while (!q.empty()) {
		int now = q.front().first;
		int cnt = q.front().second;
		q.pop();

		if (now == g) {
			return cnt;
		}
		
		if (now + u <= f) {
			if (!visited[now + u]) {
				visited[now + u] = 1;
				q.push({ now + u, cnt + 1 });
			}
		}
		
		if (now - d > 0) {
			if (!visited[now - d]) {
				visited[now - d] = 1;
				q.push({ now - d, cnt + 1 });
			}
		}
	}
	return -1;
}

int main(){

	cin >> f >> s >> g >> u >> d;
	
	int res = bfs();

	if (res == -1) cout << "use the stairs" << "\n";
	else cout << res << "\n";

	return 0;
}