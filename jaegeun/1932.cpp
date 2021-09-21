// 정수 삼각형
// https://www.acmicpc.net/problem/1932

#include <iostream>
#include <algorithm>

using namespace std;

int n = 0;
int tri[500][500];
int dp[500][500];


int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			cin >> tri[i][j];
		}
	}
	dp[0][0] = tri[0][0];
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0)
			{
				dp[i][0] = dp[i - 1][0] + tri[i][j];
			}
			else if(j == i)
			{
				dp[i][j] = dp[i - 1][j - 1] + tri[i][j];
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + tri[i][j];
			}
		}
	}
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		if (dp[n - 1][i] > result) result = dp[n - 1][i];
	}
	cout << result << endl;
	return 0;
}