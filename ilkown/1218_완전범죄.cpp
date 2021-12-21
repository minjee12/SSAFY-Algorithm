#include <iostream>
#include <queue>
using namespace std;
#define max 100001

int n, s, d, f, b, k;
//건물수, 금은방 위치, 대도 집, 전진 후진 속도, 경찰서 개수

int map[max] = {};
int visited[max] = {};
int ans = -1;
int dir[2] = {};
struct node {
	int cur;
	int lev;
};

void crime(int cur) {
	queue<node> que;
	que.push({ cur,0 });
	visited[cur] = 1;

	while (!que.empty()) {
		cur = que.front().cur;
		int lev = que.front().lev;
		que.pop();

		if (cur == d) {
			ans = lev;
			break;
		}

		for (int i = 0; i < 2; i++) {
			int next = cur + dir[i];
			if (next < 1 || next > n || map[next] == 1) continue;
			if (visited[next] == 1) continue;
			visited[next] = 1;
			que.push({ next,lev + 1 });
		}

	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(null);
	cout.tie(null);

	cin >> n >> s >> d >> f >> b >> k;
	for (int i = 0; i < k; i++) {
		int a;
		cin >> a;
		map[a] = 1;
	}
	dir[0] = f;
	dir[1] = -b;
	crime(s);

	if (ans == -1) {
		cout << "bug found\n";
	}
	else {
		cout << ans << "\n";
	}

	return 0;
}