#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <memory.h>
using namespace std;
#define MAX 21

int map[MAX][MAX] = {};
int used[101] = {};
int N;
int dir[4][2] = { {1,1},{1,-1},{-1,-1},{-1,1} };
int ans = -1;

int isInside(int y, int x) {
	if (y < 0 || y >= N || x < 0 || x >= N) return 0;
	return 1;
}
void dfs(int y, int x, int start_y, int start_x, int lev, int d) {

	if (d == 4) return;
	if (y == start_y && x == start_x) {
		if (ans < lev) ans = lev;
		return;
	}

	if (!isInside(y, x)) return;

	if (used[map[y][x]] == 0) {
		used[map[y][x]] = 1;
		int ny = y + dir[d][0];
		int nx = x + dir[d][1];

		dfs(ny, nx, start_y, start_x, lev + 1, d); //오른쪽 아래부터 진행
		
		int ry = y + dir[d + 1][0];
		int rx = x + dir[d + 1][1];
		
		dfs(ry, rx, start_y, start_x, lev + 1, d + 1); //왼쪽 아래부터 진행
		used[map[y][x]] = 0;
	}
	else return;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int tc;

	freopen("./sample_input.txt", "r", stdin);

	cin >> tc;

	int k = 1;
	while (tc--) {
		cin >> N;

		ans = -1;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				used[map[y][x]] = 1;
				dfs(y + 1, x + 1, y, x, 1, 0);
				used[map[y][x]] = 0;
			}
		}

		
		cout << "#" << k++ << " " << ans << "\n";
	}


	return 0;
}