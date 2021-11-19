// 동전 1
// 

#include <iostream>

using namespace std;

int N, K;
int coins[100];


int dp[10001];

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> N >> K;

	for (int i = 0; i < N; i++) cin >> coins[i];

	dp[0] = 1; // 0원 만드는 경우의 수 1개
	// coin[i]로 만들 수 있는 경우의 수를 증가시킴
	for (int i = 0; i < N; i++) {
		for (int j = coins[i]; j <= K; j++) {
			dp[j] += dp[j - coins[i]];
		}
	}
	cout << dp[K];
	return 0;
}