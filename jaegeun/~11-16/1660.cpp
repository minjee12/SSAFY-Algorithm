// 캡틴 이다솜
// https://www.acmicpc.net/problem/1660

#include <iostream>

using namespace std;

int idx = 0; // 최대 갯수
int cnt = 0;
int tet[1000];
int dp[300001];

int main() {
	//freopen_s(new FILE*, "text.txt", "r", stdin);
	int N; cin >> N;
	for (int i = 1; i <= 1000; i++) {
		for (int j = 1; j <= i; j++) {
			tet[i] += j * (j + 1) / 2;
		}
		if (tet[i] > N) {
			idx = i - 1; 
			break;
		}
	}
	fill(dp, dp + 300001, 1e7);

	for (int i = 1; i <= idx; i++) {
		dp[tet[i]] = 1;
	}
	
	for (int i = 1; i <= idx; i++) {
		for (int j = tet[i]; j <= N; j++) {
			dp[j] = min(dp[j], dp[j - tet[i]] + 1);
		}
	}
	cout << dp[N];
	return 0;
}
