// 마법사 상어와 토네이도
// 문제 이해 잘 하기!
// alpha는 55%가 아님. 나머지에 퍼지고 %계산 버려진 값도 포함.
#include<iostream>
using namespace std;

int N;
int arr[500][500];
int dir = 0, out = 0; // 방향, 나간 모래 양
int sum = 0;
typedef struct {
	int y, x;
} D;
D d[4][10] = {
	{{-1,1},{-1,0},{-1,-1},{1,-1},{1,0},{1,1},{-2,0},{0,-2},{2,0},{0,-1}},
	{{-1,-1},{0,-1},{1,-1},{1,1},{0,1},{-1,1},{0,-2},{2,0},{0,2},{1,0}},
	{{-1,-1},{-1,0},{-1,1},{1,1},{1,0},{1,-1},{-2,0},{0,2},{2,0},{0,1}},
	{{1,-1},{0,-1},{-1,-1},{-1,1},{0,1},{1,1},{0,-2},{-2,0},{0,2},{-1,0}}
};

D go[4] = { {0,-1},{1,0},{0,1},{-1,0} };
int percent[10] = { 1,7,10,10,7,1,2,5,2,0 };

void run() {
	int y = N / 2;
	int x = N / 2;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < 2; j++) {  //2번씩
			for (int k = 1; k <= i; k++) {  // 한번 당 이동 칸 수
				int val = dir % 4;
				y = y + go[val].y;
				x = x + go[val].x;
				int s = arr[y][x]; // 이동한 칸에 있는 모래 양
				for (int l = 0; l < 9; l++) {
					int dy = y + d[val][l].y;
					int dx = x + d[val][l].x;
					sum = sum + ((s * percent[l]) / 100);
					if (dy < 0 || dx < 0 || dy >= N || dx >= N) out = out + ((s * percent[l]) / 100);
					else {
						arr[dy][dx] = arr[dy][dx] + ((s * percent[l]) / 100);
					}
				}
				int dy = y + d[val][9].y;
				int dx = x + d[val][9].x;
				int alpha = s - sum;
				if (dy < 0 || dx < 0 || dy >= N || dx >= N) out = out + alpha;
				else {
					arr[dy][dx] = arr[dy][dx] + alpha;
				}

				arr[y][x] = 0;
				sum = 0;

				if (k == i) dir++;
			}
		}
	}
	for (int k = 1; k < N; k++) {  // 한번 당 이동 칸 수
		int val = dir % 4;
		y = y + go[val].y;
		x = x + go[val].x;
		int s = arr[y][x]; // 이동한 칸에 있는 모래 양
		for (int l = 0; l < 9; l++) {
			int dy = y + d[val][l].y;
			int dx = x + d[val][l].x;
			sum = sum + ((s * percent[l]) / 100);
			if (dy < 0 || dx < 0 || dy >= N || dx >= N) out = out + ((s * percent[l]) / 100);
			else {
				arr[dy][dx] = arr[dy][dx] + ((s * percent[l]) / 100);
			}
		}
		int dy = y + d[val][9].y;
		int dx = x + d[val][9].x;
		int alpha = s - sum;
		if (dy < 0 || dx < 0 || dy >= N || dx >= N) out = out + alpha;
		else {
			arr[dy][dx] = arr[dy][dx] + alpha;
		}

		arr[y][x] = 0;
		sum = 0;
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
	}// 초기 위치는 arr[N/2][N/2]

	run();
	cout << out;
	return 0;
}