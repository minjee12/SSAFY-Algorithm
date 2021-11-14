#include <iostream>
#include <queue>
using namespace std;
#define MAX 1000000

int F, S, G, U/*À§·Î UÃþ*/, D/*¾Æ·¡·Î DÃþ*/;
int visited[MAX + 1] = {};
int button[2] = {};
struct Node {
	int str;
	int lev = 0;
};


int bfs() {

	queue<Node> que;
	que.push({ S,0 });
	visited[S] = 1;

	while (!que.empty()) {
		int stair = que.front().str;
		int lev = que.front().lev;
		que.pop();

		if (stair == G) return lev;

		for (int i = 0; i < 2; i++) {
			int ns = stair + button[i];
			if (ns >= 1 && ns <= F && visited[ns] != 0) {
				visited[ns] = 1;
				que.push({ ns,lev + 1 });
			}
		}

	}

	return -1;
}

int main() {

	ios::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	cin >> F >> S >> G >> U >> D;

	button[0] = U;
	button[1] = -D;

	int ans = bfs();

	if (ans == -1) cout << "use the stairs" << endl;
	else cout << ans << endl;

	return 0;
}