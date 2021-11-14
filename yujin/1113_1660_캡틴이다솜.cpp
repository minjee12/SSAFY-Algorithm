#include <iostream>
#include <algorithm>
using namespace std;

int level[300] = { 0, }; //level[i] = ���̰� i�� �ﰢ���� �ʿ��� ������ ����
int total[300] = { 0, }; //total[i] = ���̰� i�� ���ü�� �ʿ��� ������ ����
int dp[300001] = { 0, }; //dp[i] = i���� �������� ������ ������ִ� ���ü�� �ּ� ����
int n;

int main() {
	cin >> n;
	for (int i = 1; i < 300; i++) {
		level[i] = i + level[i - 1];
	}
	for (int i = 1; i < 300; i++) {
		total[i] = level[i] + total[i - 1];
	}
	for (int i = 1; i <= n; i++) { //���ü�� ����� �ִ� �ּ� ������ 1�� ���� �� �ִ� ���ü ����
		dp[i] = i;
	}

	//dp[n] ���ϱ�
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