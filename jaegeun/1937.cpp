// 욕심쟁이 판다
// https://www.acmicpc.net/problem/1937

#include <iostream>

#define MAX 501

using namespace std;

int N = 0;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
int forest[MAX][MAX];
int dp[MAX][MAX];

int dfs(int x, int y)
{
	if (dp[x][y]) return dp[x][y];
	dp[x][y] = 1;
	for (int i = 0; i < 4; i++)
	{
		int nx = dx[i] + x;
		int ny = dy[i] + y;

		if (nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;
		if (forest[x][y] >= forest[nx][ny]) continue;
		dp[x][y] = max(dp[x][y], dfs(nx, ny) + 1);
	}
	return dp[x][y];
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> forest[i][j];
		}
	}
	int max_result = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			max_result = max(max_result, dfs(i, j));
		}
	}
	cout << max_result << '\n';
	return 0;
}