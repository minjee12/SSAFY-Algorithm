#include <iostream>
using namespace std;

int n;
int l;
int map[101][101];

bool check_y(int y) {
	int start = map[y][0];
	int prev = 1;
	for (int i = 1; i < n; i++) {
		if (start == map[y][i]) prev++;
		else if (start == map[y][i] - 1) { //ÇÑÄ­ ³ôÀ¸¸é
			if (prev >= l) prev = 1;
			else return false;
		}
		else if (start == map[y][i] + 1) { //ÇÑÄ­ ³·À¸¸é
			for (int j = 0; j < l; j++) {
				if (j == n) return false;
				if (map[y][i + j] == map[y][i]) continue;
				else return false;
			}
			i = i + l - 1;
			prev = 0;
		}
		else return false;
		start = map[y][i];
	}

	return true;
}

bool check_x(int x) {
	int start = map[0][x];
	int prev = 1;
	for (int i = 1; i < n; i++) {
		if (start == map[i][x]) prev++;
		else if (start == map[i][x] - 1) { //ÇÑÄ­ ³ôÀ¸¸é
			if (prev >= l) prev = 1;
			else return false;
		}
		else if (start == map[i][x] + 1) { //ÇÑÄ­ ³·À¸¸é
			for (int j = 0; j < l; j++) {
				if (j == n) return false;
				if (map[i + j][x] == map[i][x]) continue;
				else return false;
			}
			i = i + l - 1;
			prev = 0;
		}
		else return false;
		start = map[i][x];
	}

	return true;
}

int main() {
	//input
	cin >> n >> l;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		if (check_y(i)) {
			res++;
		}
		if (check_x(i)) {
			res++;
		}
	}

	cout << res << "\n";
	return 0;
}