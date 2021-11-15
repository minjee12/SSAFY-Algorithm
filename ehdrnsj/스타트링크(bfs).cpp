#include <iostream>
#include <queue>
using namespace std;

int F, S, G;
int UD[2];

int used[1000001];

struct node {
	int lv;
	int floor;
};

void bfs() {
	queue<node> gangho;
	gangho.push({0, S});

	while (!gangho.empty()) {
		node now = gangho.front();
		gangho.pop();

		if (now.floor == G) {
			cout << now.lv;
			return;
		}

		for (int i = 0; i < 2; i++) {
			int nextFloor = now.floor + UD[i];
			if (nextFloor < 1 || nextFloor > F) continue;
			if (used[nextFloor] == 1) continue;
			used[nextFloor] = 1;

			gangho.push({ now.lv + 1, nextFloor });
		}
	}
	cout << "use the stairs";
}

int main() {
	cin >> F >> S >> G;
	cin >> UD[0] >> UD[1];
	UD[1] *= -1;

	bfs();

	return 0;
}