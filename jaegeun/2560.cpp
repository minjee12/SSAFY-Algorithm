// 짚신벌레
// https://www.acmicpc.net/problem/2560

#include <iostream>

using namespace std;

int dp[1000001] = { 0, };

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int start, end, death, N;
	cin >> start>> end>> death>> N;
	
    dp[0] = 1;

    for (int i = 1; i <= N; i++) {
        if (i < start)
            dp[i] = dp[i - 1] % 1000;
        else if (i < end)
            dp[i] = (dp[i - 1] + dp[i - start]) % 1000;
        else
            dp[i] = (dp[i - 1] + dp[i - start] - dp[i - end] + 1000) % 1000;
    }

    if (N - death >= 0)
        cout << (dp[N] - dp[N - death] + 1000) % 1000;
    else
        cout << dp[N] % 1000;
}