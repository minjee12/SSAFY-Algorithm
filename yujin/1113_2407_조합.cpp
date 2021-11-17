#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

//전역변수로 메모이제이션 선언.
string dp[102][102];

//사용되는 변수가 변하지 않도록 const로 선언하였다.
string string_add(const string num1, const string num2) {
	long long sum = 0;
	//num을 copy에 복사하였다.
	string copy1(num1), copy2(num2);
	string ret;

	//copy1, copy2, sum이 모두 비어있을때까지 계산을 계속한다.
	while (!copy1.empty() || !copy2.empty() || sum) {
		if (!copy1.empty()) {
			//copy1에 있는 마지막 문자는 char형태로 저장되어있으므로(ascii형식) '0'을 빼주어 정수화 해주었다.
			sum += copy1.back() - '0';
			copy1.pop_back();
		}
		if (!copy2.empty()) {
			sum += copy2.back() - '0';
			copy2.pop_back();
		}
		//sum의 일의 자릿수를 ret에 넣어주자.(이때, char형으로 들어가므로 다시 '0'을 더해준다)
		ret.push_back((sum % 10) + '0');
		sum /= 10;
	}
	//역순으로 입력되어있으므로, reverse함수를 활용해 문자열을 뒤집는다.
	reverse(ret.begin(), ret.end());
	return ret;
}


string combi(int n, int m) {
	if (n == m || m == 0) {
		//n==m이거나 m==0인 경우 string 1을 리턴한다.
		return "1";
	}
	if (dp[n][m] != "") {
		return dp[n][m];
	}
	//재귀호출을 하여 반복한다.
	return dp[n][m] = string_add(combi(n - 1, m - 1), combi(n - 1, m));
}



int main() {
	int n, m;
	cin >> n >> m;
	cout << combi(n, m);
}
