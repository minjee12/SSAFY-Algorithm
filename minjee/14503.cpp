// 로봇청소기
// 0 북 -> 서 남 동
// 1 동 -> 북 서 남
// 2 남 -> 동 북 서
// 3 서 -> 남 동 북
#include<iostream>

using namespace std;

int N, M, d;
int ret = 1, cnt = 0;
bool arr[50][50];
bool ch[50][50];
typedef struct {
	int y, x;
} Dir;

Dir di[4] = { {0,-1},{-1,0},{0,1},{1,0} }; // 서 북 동 남


void run(int* r, int* c) {
	ch[*r][*c] = true; // 처음 위치 청소
	int y = *r + di[d].y;
	int x = *c + di[d].x;
	if (cnt == 4) {
		cnt = 0;
		y = *r + di[(d + 3) % 4].y;
		x = *c + di[(d + 3) % 4].x;
		if (arr[y][x] == 1 || y < 0 || x < 0 || y >= N || x >= M) return;
		run(&y, &x);
		return;
	}
	if (y >= 0 && x >= 0 && y < N && x < M && arr[y][x] == 0 && !ch[y][x]) {
		d = (d + 3) % 4;
		ret++;
		ch[y][x] = true;
		cnt = 0;
		run(&y, &x);
		return;
	}
	else {
		d = (d + 3) % 4;
		cnt++;
		run(r, c);
		return;
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int r, c;
	cin >> N >> M; // 행, 열
	cin >> r >> c >> d;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	run(&r, &c);

	cout << ret;
	return 0;
}