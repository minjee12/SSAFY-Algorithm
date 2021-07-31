#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

int A[50][50];
bool c[50][50];
int N;
typedef struct {
	int x, y;
} Dir;

Dir d[4] = { {1,0}, {0,1}, {-1,0}, {0,-1} };

bool valid = true;

bool check(int x, int y, int l, int r) {
	for (int i = 0; i < 4; i++)
	{
		int nx = x + d[i].x;
		int ny = y + d[i].y;
		if (nx >= 0 && ny >= 0 && nx < N && ny < N)
		{
			int diff = abs(A[x][y] - A[nx][ny]);
			if (diff >= l && diff <= r) return true;
		}
	}
	return false;
}

void bfs(int x, int y, int l, int r) {
	int sum = 0;
	int cnt = 0;
	queue<Dir> q1, q2;
	q1.push({ x, y });
	q2.push({ x, y });
	c[x][y] = true;
	while (!q1.empty()) {
		int Y = q1.front().y;
		int X = q1.front().x;
		q1.pop();
		sum += A[X][Y];
		cnt++;
		for (int i = 0; i < 4; i++) {
			int ny = Y + d[i].y;
			int nx = X + d[i].x;

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (c[nx][ny]) continue;
			int diff = abs(A[X][Y] - A[nx][ny]);
			if (diff >= l && diff <= r) {
				c[nx][ny] = 1;
				q1.push({ nx, ny });
				q2.push({ nx, ny });

			}

		}
	}
	int num = sum / cnt;

	while (!q2.empty()) {
		int X = q2.front().x;
		int Y = q2.front().y;
		q2.pop();
		A[X][Y] = num;
	}
}

int main() {

	int L, R;
	int ret = 0;
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}

	while (valid) {
		valid = false;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (c[i][j] == 0 && check(i, j, L, R))
				{
					bfs(i, j, L, R);
					valid = true;
				}
			}
		}
		if (valid == true) ret++;
		memset(c, 0, sizeof(c));

	}
	cout << ret;

	return 0;
}