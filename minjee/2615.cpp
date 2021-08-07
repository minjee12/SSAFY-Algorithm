//x좌표 y좌표 범위설정!!
#include<iostream>
using namespace std;

int arr[20][20];
bool flag = false; // 이긴사람 나왔는지 판단
bool slash = false;
typedef struct {
	int y, x;
} Dir;

Dir d[8] = { {-1,-1},{1,1},{-1,1},{1,-1},{1,0},{0,1},{-1,0},{0,-1} };

int ret = 0, retY, retX;

void func(int y, int x) {
	for (int i = 0; i < 8; i++) {
		int cnt = 1;
		int ny = y + d[i].y;
		int nx = x + d[i].x;
		int dy = y - d[i].y;
		int dx = x - d[i].x;

		if (arr[ny][nx] == arr[y][x] && nx > 0 && ny > 0 && ny < 20 && nx < 20) {
			cnt++;
			int nny = ny + d[i].y;
			int nnx = nx + d[i].x;
			while (true) {
				if (arr[nny][nnx] != arr[y][x] || nnx < 1 || nny < 1 || nny > 19 || nnx > 19) break;
				else cnt++;
				nny += d[i].y;
				nnx += d[i].x;
			}
		}

		if (arr[dy][dx] == arr[y][x] && dx > 0 && dy > 0 && dy < 20 && dx < 20) {
			cnt++;
			int ddy = dy - d[i].y;
			int ddx = dx - d[i].x;
			while (true) {
				if (arr[ddy][ddx] != arr[y][x] || ddx < 1 || ddy < 1 || ddy > 19 || ddx > 19) break;
				else cnt++;
				ddy -= d[i].y;
				ddx -= d[i].x;
			}
		}
		if (cnt == 5) {
			flag = true;
			if (i == 2) slash = true;
			else slash = false;
			return;
		}
		else if (cnt > 5) {
			flag = false;
			continue;
		}
	}
}

int main() {
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j < 20; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j < 20; j++) {
			if (arr[i][j] == 1 || arr[i][j] == 2) {
				func(i, j);
				if (flag == true) {
					if (slash == true) {
						ret = arr[i + 4][j - 4];
						retY = i + 4;
						retX = j - 4;
					}
					else {
						ret = arr[i][j];
						retY = i;
						retX = j;
					}
					break;
				}
			}
		}
		if (flag == true) break;
	}
	if (ret == 0) cout << 0;
	else {
		cout << ret << "\n";
		cout << retY << " " << retX;
	}
	return 0;
}