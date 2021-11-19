#include <iostream>
using namespace std;

int n, k;
int value[101] = { 0, };
int dp[10001];

int main() {

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> value[i];
	}

	//아무 동전을 선택하지 않은 경우
	dp[0] = 1;

	for (int i = 0; i < n; i++) {//value[i]={1,2,5}
		for (int j = value[i]; j <= k; j++) {
			dp[j] = dp[j] + dp[j - value[i]];
		}
	}

	cout << dp[k] << "\n";
	return 0;
}
