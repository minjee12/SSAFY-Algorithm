// 내리막길
// https://www.acmicpc.net/problem/1520

#include <iostream>

#define MAX 501
using namespace std;

// 높이, 너비
int M = 0, N = 0;
int height[MAX][MAX];
bool visited[MAX][MAX];
int dp[MAX][MAX];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int  dfs(int x, int y)
{
	if (x == M - 1 && y == N - 1) return 1;
	if (visited[x][y]) return dp[x][y];
	visited[x][y] = 1;
	for (int i = 0; i < 4; i++)
	{
		int nx = dx[i] + x;
		int ny = dy[i] + y;

		if (nx < 0 || nx > M - 1 || ny < 0 || ny > N - 1) continue;
		if (height[nx][ny] >= height[x][y]) continue;
		dp[x][y] += dfs(nx, ny);
	}
	return dp[x][y];
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> M >> N;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++)
		{
			cin >> height[i][j];
		}
	}
	cout << dfs(0, 0) << '\n';
	return 0;
} 