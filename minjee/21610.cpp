// 마법사상어와 비바라기
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int N, M;
int A[50][50];
int go[100][2]; // 방향, 거리
bool c[50][50]; // 3에서 구름이 사라진 칸인지 체크

typedef struct {
	int y, x;
} Dir;

Dir d[9] = { {0,0},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1} };

queue<Dir> q; // 구름 위치
queue<Dir> w; // 물이 증가한 칸(물복사버그 시전할 칸 = 구름이 사라진 칸)

void newCloud() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j] >= 2 && c[i][j] == false) {
				q.push({ i,j });
				A[i][j] -= 2;
			}
		}
	}
}

// 대각선: 인덱스 2,4,6,8
void bug() {
	while (!w.empty()) {
		int y = w.front().y;
		int x = w.front().x;
		for (int i = 2; i <= 8; i += 2) {
			int dy = y + d[i].y;
			int dx = x + d[i].x;
			if (dy < 0 || dy >= N || dx < 0 || dx >= N) continue;
			if (A[dy][dx] > 0) A[y][x]++;
		}
		w.pop();
		c[y][x] = true;
	}

	newCloud();
}


void move(int direc, int s) {
	// queue에 있는 구름 하나씩 1,2,3번 수행
	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int ny = y + d[direc].y * s;
		int nx = x + d[direc].x * s;
		if (ny > N - 1) {
			while (ny > N - 1) {
				ny = ny - N;
			}
		}
		else if (ny < 0) {
			while (ny < 0) {
				ny = ny + N;
			}
		}
		if (nx > N - 1) {
			while (nx > N - 1) {
				nx = nx - N;
			}
		}
		else if (nx < 0) {
			while (nx < 0) {
				nx = nx + N;
			}
		}

		A[ny][nx]++;
		w.push({ ny,nx });
		q.pop();
	}

	bug();
}

void run() {
	for (int i = 0; i < M; i++) {
		int d = go[i][0];
		int s = go[i][1];

		move(d, s);
		memset(c, false, sizeof(c));
	}
}

int waterSum() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ret += A[i][j];
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	// 입력
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < 2; j++) {
			cin >> go[i][j];
		}
	}
	// 초기 구름 push
	q.push({ N - 1, 0 });
	q.push({ N - 1, 1 });
	q.push({ N - 2, 0 });
	q.push({ N - 2, 1 });

	run();

	int result = waterSum();
	cout << result;

	return 0;
}