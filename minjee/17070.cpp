// 파이프 옮기기1

// state 1: 가로  2: 세로  3: 대각선
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

int N;
int cnt = 0;
int arr[16][16];
typedef struct {
	int y, x;
	int state;
} Dir;

Dir d[3] = { {0,1},{1,1},{1,0} }; // 가로, 대각선, 세로
queue<Dir> q;

void one(int y, int x) { // state가 1 (가로방향) 일때
	if (arr[y][x + 1] == 1 || x + 1 >= N) q.pop(); // row+1에 빈공간이 없으면 pop
	else {
		q.push({ y, x + 1, 1 }); // 가로 push
		if (y + 1 < N && arr[y][x + 1] == 0 && arr[y + 1][x + 1] == 0 && arr[y + 1][x] == 0) q.push({ y + 1, x + 1, 3 }); // 대각선 push
		q.pop();
	}
}

void two(int y, int x) { // state가 2 (세로방향) 일때
	if (arr[y + 1][x] == 1 || y + 1 >= N) q.pop(); // column+1에 빈공간이 없으면 pop
	else {
		q.push({ y + 1, x, 2 }); // 세로 push
		if (x + 1 < N && arr[y][x + 1] == 0 && arr[y + 1][x + 1] == 0 && arr[y + 1][x] == 0) q.push({ y + 1, x + 1, 3 }); // 대각선 push
		q.pop();
	}
}

void three(int y, int x) { // state가 3 (대각선방향) 일때
	if (y + 1 < N && x + 1 < N && arr[y][x + 1] == 0 && arr[y + 1][x + 1] == 0 && arr[y + 1][x] == 0) q.push({ y + 1, x + 1, 3 }); // 대각선 push
	if (x + 1 < N && arr[y][x + 1] == 0) q.push({ y, x + 1, 1 }); // 가로 push
	if (y + 1 < N && arr[y + 1][x] == 0) q.push({ y + 1, x, 2 }); // 세로 push
	q.pop();
}

void run() {
	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		if (y == N - 1 && x == N - 1) cnt++;
		int state = q.front().state;
		if (state == 1) {
			one(y, x);
		}
		else if (state == 2) {
			two(y, x);
		}
		else if (state == 3) {
			three(y, x);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	q.push({ 0,1,1 });
	run();
	cout << cnt;

	return 0;
}