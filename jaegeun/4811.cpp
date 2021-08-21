// 알약
// https://www.acmicpc.net/problem/4811

// 카탈랑 수
#include <iostream>

using namespace std;
int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	long long dp[31] = { 0, };

	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i < 31; i++)
	{
		long long cnt = 0;
		for (int j = 0; j < i; j++)
		{
			cnt += dp[j] * dp[i - 1 - j];
		}
		dp[i] = cnt;
	}

	while (true)
	{
		int n = 0;
		cin >> n;
		if (n == 0) break;
		cout << dp[n] << endl;
	}
	return 0;
}