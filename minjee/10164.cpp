#include<iostream>
using namespace std;

int N, M, K;
int dp[15][15];
typedef struct{
	int y,x;
} Dir;

Dir circle;

int main() {
	int cnt = 1;
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (cnt == K) circle = { i, j };
			cnt++;

			if (i == 0 || j == 0) dp[i][j] = 1;
			else dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	int y = circle.y;
	int x = circle.x;
	cout << dp[y][x] * dp[N - 1 - y][M - 1 - x];
	return 0;
}