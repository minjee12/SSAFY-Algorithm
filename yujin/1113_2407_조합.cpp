#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

//���������� �޸������̼� ����.
string dp[102][102];

//���Ǵ� ������ ������ �ʵ��� const�� �����Ͽ���.
string string_add(const string num1, const string num2) {
	long long sum = 0;
	//num�� copy�� �����Ͽ���.
	string copy1(num1), copy2(num2);
	string ret;

	//copy1, copy2, sum�� ��� ������������� ����� ����Ѵ�.
	while (!copy1.empty() || !copy2.empty() || sum) {
		if (!copy1.empty()) {
			//copy1�� �ִ� ������ ���ڴ� char���·� ����Ǿ������Ƿ�(ascii����) '0'�� ���־� ����ȭ ���־���.
			sum += copy1.back() - '0';
			copy1.pop_back();
		}
		if (!copy2.empty()) {
			sum += copy2.back() - '0';
			copy2.pop_back();
		}
		//sum�� ���� �ڸ����� ret�� �־�����.(�̶�, char������ ���Ƿ� �ٽ� '0'�� �����ش�)
		ret.push_back((sum % 10) + '0');
		sum /= 10;
	}
	//�������� �ԷµǾ������Ƿ�, reverse�Լ��� Ȱ���� ���ڿ��� �����´�.
	reverse(ret.begin(), ret.end());
	return ret;
}


string combi(int n, int m) {
	if (n == m || m == 0) {
		//n==m�̰ų� m==0�� ��� string 1�� �����Ѵ�.
		return "1";
	}
	if (dp[n][m] != "") {
		return dp[n][m];
	}
	//���ȣ���� �Ͽ� �ݺ��Ѵ�.
	return dp[n][m] = string_add(combi(n - 1, m - 1), combi(n - 1, m));
}



int main() {
	int n, m;
	cin >> n >> m;
	cout << combi(n, m);
}
