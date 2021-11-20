#include <iostream>

using namespace std;

int N;
char map[6][7];

pair<int, int> teachers[5];
int num;

int direct[4][2] = {
	-1,0,
	0,1,
	1,0,
	0,-1
};

int possible;

int check() {
	for (int n = 0; n < num; n++) {
		int starty = teachers[n].first;
		int startx = teachers[n].second;

		for (int t = 0; t < 4; t++) {
			int nexty = starty;
			int nextx = startx;
			//int barricade = 0;
			while (1) {
				nexty += direct[t][0];
				nextx += direct[t][1];
				if (nexty < 0 || nextx < 0 || nexty >= N || nextx >= N) break;

				if (map[nexty][nextx] == 'S') return -1;
				else if (map[nexty][nextx] == 'O') break;
			}
		}
	}
	return 1;
}

void bt(int lv, int Y, int X) {
	if (lv == 3) {
		possible = check();
		return;
	}

	for (int y = Y; y < N; y++) {
		for (int x = X; x < N; x++) {
			if (map[y][x] != 'X') continue;
			map[y][x] = 'O';
			bt(lv + 1, y, x);
			if (possible == 1) return;
			map[y][x] = 'X';
		}
		X = 0;
	}
}

int main() {
	cin >> N;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
			if (map[y][x] == 'T')
				teachers[num++] = { y, x };
		}
	}

	bt(0, 0, 0);

	if (possible == 1) cout << "YES";
	else if (possible == -1) cout << "NO";

	return 0;
}