// 조합
// https://www.acmicpc.net/problem/2407

#include <iostream>
#include <string>

#define MAX 101
using namespace std;

int N, M;
string dp[MAX][MAX];

string add_num(string a, string b) {
	int len_a = a.length();
	int len_b = b.length();
	string result = "";
	
	int carr = 0;
	while (1) {
		if (len_a == 0 || len_b == 0) break;
		int s = int(a[--len_a] - '0') + int(b[--len_b] - '0');
		
		if (carr) s++;
		if (s >= 10) {
			result = char('0' + (s % 10)) + result;
			carr = 1;
		}
		else {
			result = char('0' + s) + result;
			carr = 0;
		}
	}

	if (len_a) {
		while (len_a) {
			int s = int(a[--len_a] - '0');
			if (carr) s++;
			
			if (s >= 10) {
				result = char('0' + (s % 10)) + result;
				carr = 1;
			}
			else {
				result = char('0' + s) + result;
				carr = 0;
			}
		}
	}
	else {
		while (len_b) {
			int s = int(b[--len_b] - '0');
			if (carr) s++;

			if (s >= 10) {
				result = char('0' + (s % 10)) + result;
				carr = 1;
			}
			else {
				result = char('0' + s) + result;
				carr = 0;
			}
		}
	}
	if (carr) {
		result = '1' + result;
	}
	return result;
}

void fill_tri() {
	for (int i = 0; i <= N; i++)
		dp[i][0] = "1";
	for (int i = 0; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			dp[i][j] = add_num(dp[i - 1][j - 1], dp[i - 1][j]);
		}
	}
}


int main() {
	
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;
	fill_tri();
	cout << dp[N][M];
	return 0;
}