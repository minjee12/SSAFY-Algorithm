// 타일 채우기
// https://www.acmicpc.net/problem/2133

#include <iostream>
#include <cmath>

using namespace std;

int dp[31] = { 0, };

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);

	dp[0] = 1;
	dp[2] = 3;

	for (int i = 4; i <= 30; i += 2) {
		dp[i] = dp[i - 2] * 3;  // 이전 칸 경우의 수 * 3 만큼 늘어남
		for (int j = 4; j <= i; j += 2) {
			dp[i] += dp[i - j] * 2; // 중간 칸도 이전 경우의 수 * 2배 만큼 늘어남
		}
	}

	int n; cin >> n;
	cout << dp[n];
	return 0;
}
