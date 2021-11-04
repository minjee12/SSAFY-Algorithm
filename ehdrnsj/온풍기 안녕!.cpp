#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node {
	int x, y;
	int n;
};

int R, C, K;
int map[21][21];

int W;
int top_wall[21][21];
int right_wall[21][21];

int direct[5][3][2] = {
	{0,0, 0,0, 0,0,},
	{-1,1, 0,1, 1,1,},
	{-1,-1,	0,-1, 1,-1,},
	{-1,-1,	-1,0, -1,1,},
	{1,-1, 1,0,	1,1,},
};

vector<node> heaters;
vector<node> watch;

int check(int x, int y, int type, int t) {
	if (x == 4 && y == 4) {
		int de = -1;
	}
	if (type == 1) {
		if (t == 0) {
			if (top_wall[x][y] == 1 || right_wall[x - 1][y] == 1) return -1;
		}
		else if (t == 1) {
			if (right_wall[x][y] == 1) return -1;
		}
		else if (t == 2) {
			if (top_wall[x + 1][y] == 1 || right_wall[x + 1][y] == 1) return -1;
		}
	}
	else if (type == 2) {
		if (t == 0) {
			if (top_wall[x][y] == 1 || right_wall[x - 1][y - 1] == 1) return -1;
		}
		else if (t == 1) {
			if (right_wall[x][y - 1] == 1) return -1;
		}
		else if (t == 2) {
			if (top_wall[x + 1][y] == 1 || right_wall[x + 1][y - 1] == 1) return -1;
		}
	}
	else if (type == 3) {
		if (t == 0) {
			if (right_wall[x][y - 1] == 1 || top_wall[x][y - 1] == 1) return -1;
		}
		else if (t == 1) {
			if (top_wall[x][y] == 1) return -1;
		}
		else if (t == 2) {
			if (right_wall[x][y] == 1 || top_wall[x][y + 1] == 1) return -1;
		}
	}
	else if (type == 4) {
		if (t == 0) {
			if (right_wall[x][y - 1] == 1 || top_wall[x + 1][y - 1] == 1) return -1;
		}
		else if (t == 1) {
			if (top_wall[x + 1][y] == 1) return -1;
		}
		else if (t == 2) {
			if (right_wall[x][y] == 1 || top_wall[x + 1][y + 1] == 1) return -1;
		}
	}
	return 1;
}

void heat(node start) {
	int map_heat[21][21] = { 0 };

	queue<node> q;
	map_heat[start.x][start.y] = 5;
	q.push({ start.x,start.y,5 });

	while (!q.empty()) {
		node now = q.front();
		q.pop();

		if (now.n == 1) break;

		for (int t = 0; t < 3; t++) {
			int X = now.x + direct[start.n][t][0];
			int Y = now.y + direct[start.n][t][1];

			if (check(now.x, now.y, start.n, t) == -1) {
				int de = -1;
				continue;
			}
			if (X < 1 || Y < 1 || X > R || Y > C) continue;
			if (map_heat[X][Y] != 0) continue;

			map_heat[X][Y] = now.n - 1;
			q.push({ X, Y, now.n - 1 });
		}
	}

	for (int x = 1; x <= R; x++) {
		for (int y = 1; y <= C; y++) {
			map[x][y] += map_heat[x][y];
		}
	}
}

int direct2[4][2] = {
	-1,0, 0,1, 1,0, 0,-1
};

void temp_jojong() {
	int temp_gap[21][21] = { 0 };

	for (int x = 1; x <= R; x++) {
		for (int y = 1; y <= C; y++) {
			for (int t = 0; t < 4; t++) {
				int X = x + direct2[t][0];
				int Y = y + direct2[t][1];

				if (t == 0 && top_wall[x][y] == 1) continue;
				else if (t == 1 && right_wall[x][y] == 1) continue;
				else if (t == 2 && top_wall[x + 1][y] == 1) continue;
				else if (t == 3 && right_wall[x][y - 1] == 1) continue;

				if (X < 1 || Y < 1 || X > R || Y > C) continue;

				temp_gap[x][y] += (map[X][Y] - map[x][y]) / 4;
			}
		}
	}

	for (int x = 1; x <= R; x++) {
		for (int y = 1; y <= C; y++) {
			map[x][y] += temp_gap[x][y];
		}
	}
}

void temp_minus1() {
	for (int x = 1; x <= R; x++) {
		for (int y = 1; y <= C; y++) {
			if (x == 1 || y == 1 || x == R || y == C) {
				if (map[x][y] == 0) continue;
				map[x][y]--;
			}
		}
	}
}

int solution() {
	int flg = 1;
	int choco = 0;
	int num_heater = heaters.size();
	int num_watch = watch.size();

	while (1) {
		for (int n = 0; n < num_heater; n++) {
			heat(heaters[n]);
		}
		temp_jojong();
		temp_minus1();
		choco++;

		if (choco > 100) return 101;
		flg = 1;
		for (int i = 0; i < num_watch; i++) {
			if (map[watch[i].x][watch[i].y] < K) {
				flg = 0;
				break;
			}
		}
		if (flg) return choco;
	}
}

int main() {
	cin >> R >> C >> K;
	for (int x = 1; x <= R; x++) {
		for (int y = 1; y <= C; y++) {
			int input;
			cin >> input;

			if (input == 1) heaters.push_back({ x, y + 1, input });
			else if (input == 2) heaters.push_back({ x, y - 1, input });
			else if (input == 3) heaters.push_back({ x - 1, y, input });
			else if (input == 4) heaters.push_back({ x + 1, y, input });
			else if (input == 5) watch.push_back({ x, y, 5 });
		}
	}

	cin >> W;
	for (int i = 0; i < W; i++) {
		int x, y, t;
		cin >> x >> y >> t;
		if (t == 0) {
			top_wall[x][y] = 1;
		}
		else if (t == 1) {
			right_wall[x][y] = 1;
		}
	}

	cout << solution();

	return 0;
}