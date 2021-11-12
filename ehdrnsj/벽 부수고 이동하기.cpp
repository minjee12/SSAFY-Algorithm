#include <iostream>
#include <string.h>
#include <deque>
#define MAX 1001
using namespace std;

char map[MAX][MAX];
int used[MAX][MAX][2];

struct node {
	int y, x;
	int lv;
	int can_break;
};
deque<node> dq;

int direct[4][2] = {
	-1, 0,
	0, 1,
	1, 0,
	0, -1
};

int move(int starty, int startx, int endy, int endx) {
	dq.push_back({ starty, startx, 1, 1 });
	used[starty][startx][0] = 1;
	used[starty][startx][1] = 1;

	while (!dq.empty()) {
		node now = dq.front();
		dq.pop_front();

		if (now.y == endy && now.x == endx) {
			return now.lv;
		}
		for (int t = 0; t < 4; t++) {
			int Y = now.y + direct[t][0];
			int X = now.x + direct[t][1];
			if (Y < 0 || X < 0 || Y > endy || X > endx) continue;

			node tmp = now;
			if (map[Y][X] == '0' && used[Y][X][tmp.can_break] == 1) continue;
			if (map[Y][X] == '1' && tmp.can_break == 0) continue;

			if (map[Y][X] == '1' && used[Y][X][tmp.can_break - 1] == 1) continue;
			else if (map[Y][X] == '1' && used[Y][X][tmp.can_break - 1] == 0) tmp.can_break--;

			tmp.y = Y;  tmp.x = X;
			tmp.lv++;

			used[tmp.y][tmp.x][tmp.can_break] = 1;
			
			dq.push_back(tmp);
		}
	}
	return -1;
}

int main() {
	int N, M;
	cin >> N >> M;

	for (int y = 0; y < N; y++) cin >> map[y];

	cout << move(0, 0, N - 1, M - 1);

	return 0;
}
