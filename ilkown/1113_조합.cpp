#include <iostream>
#include <string>
using namespace std;

//Á¶ÇÕ;
//nCm
// -> (n)*(n-1)* .. m°³
// -> / m!

int N, M;
string dp[101][101] = {};

string bigInt(string num1, string num2) {
	
	int sum = 0;
	string result;

	while (!num1.empty() || !num2.empty() || sum) {
		if (!num1.empty()) {
			sum += num1.back() - '0';
			num1.pop_back();
		}
		if (!num2.empty()) {
			sum += num2.back() - '0';
			num2.pop_back();
		}
		result.push_back((sum % 10) + '0');
		sum /= 10;
	}
	reverse(result.begin(), result.end());

	return result;
}

string combination(int n , int m) {

	if (n == m || m == 0) return "1";

	string& result = dp[n][m];

	if (result != "") return result;

	result = bigInt(combination(n - 1, m - 1), combination(n - 1, m));

	return result;
}


int main() {

	ios::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	cin >> N >> M;

	string ans = combination(N, M);

	cout << ans << endl;

	return 0;
}