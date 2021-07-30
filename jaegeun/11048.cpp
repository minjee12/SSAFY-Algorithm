#include <iostream>

using namespace std;

int map[1001][1001] = { 0 };
int dp[1001][1001] = { 0, };
int n = 0, m = 0;

int max(int x, int y)
{
	return x >= y ? x : y;
}

int main()
{
	freopen_s(new FILE*, "input.txt", "r", stdin);

	cin >> n >> m;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{

			cin >> map[i][j];
		}
	}
	
	dp[0][0] = map[0][0];

	for (int i = 1; i < m; i++)
	{
		dp[0][i] = dp[0][i - 1] + map[0][i];
	}

	for (int i = 1; i < n; i++)
	{
		dp[i][0] = dp[i - 1][0] + map[i][0];
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			dp[i][j] = max(dp[i - 1][j] + map[i][j], dp[i][j - 1] + map[i][j]);
		}
	}
	cout << dp[n - 1][m - 1];
	return 0;
}