#include <iostream>
#include <algorithm>
using namespace std;

int level[300] = { 0, }; //level[i] = 길이가 i인 삼각형에 필요한 대포알 개수
int total[300] = { 0, }; //total[i] = 길이가 i인 사면체에 필요한 대포알 개수
int dp[300001] = { 0, }; //dp[i] = i개의 대포알을 가지고 만들수있는 사면체의 최소 개수
int n;

int main() {
	cin >> n;
	for (int i = 1; i < 300; i++) {
		level[i] = i + level[i - 1];
	}
	for (int i = 1; i < 300; i++) {
		total[i] = level[i] + total[i - 1];
	}
	for (int i = 1; i <= n; i++) { //사면체를 만들수 있는 최소 개수인 1로 만들 수 있는 사면체 개수
		dp[i] = i;
	}

	//dp[n] 구하기
	int idx = 1;
	while (total[idx] <= n) { 
		for (int i = 1; i <= n; i++) {
			if (i >= total[idx]) {
				dp[i] = min(dp[i], dp[i - total[idx]] + 1);
			}
		}
		idx += 1;
	}

	cout << dp[n] << "\n";
	
	return 0;
}