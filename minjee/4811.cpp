#include<iostream>
using namespace std;

long long int dp[31][30];
long long int tot[31];
int main() {
	int N;
	tot[1] = 1;
	tot[2] = 2;
	dp[2][0] = 1;
	dp[2][1] = 1;
	for (int i = 3; i < 31; i++) {
		for (int j = 0; j < i; j++) {
			if (j == 0 || j == 1) dp[i][j] = tot[i - 1];
			else {
				dp[i][j] = dp[i][j - 1] - dp[i - 1][j - 2];
			}
			tot[i] += dp[i][j];
		}
	}

	while (true) {
		cin >> N;
		if (N == 0) break;
		cout << tot[N] << "\n";
	}
	return 0;
}