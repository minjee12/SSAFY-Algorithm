// 연속합
// https://www.acmicpc.net/problem/1912

#include <iostream>
#define MAX 100000

using namespace std;

int arr[MAX];
int dp[MAX];

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];

	dp[0] = arr[0];

	int result = dp[0];
	for (int i = 1; i < n; i++)
	{
		dp[i] = max(dp[i - 1] + arr[i], arr[i]);
		result = max(dp[i], result);
	}

	cout << result << '\n';
	return 0;
}