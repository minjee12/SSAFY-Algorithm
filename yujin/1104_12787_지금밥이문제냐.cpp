#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void dec2ip(unsigned long long num) {
	string ans = "";
	unsigned long long tmp = 0; 
	int idx = 7;
	while (idx >= 0) {
		unsigned long long div = pow(256, idx);
		tmp = num / div;
		ans += to_string(tmp);
		ans += '.';
		num %= div;
		idx--;
	}
	for (int i = 0; i < ans.size() - 1; i++) {
		cout << ans[i];
	}
	cout << "\n";
}

int main() {
	int test_case = 0;
	cin >> test_case;
	while (test_case--) {
		int n = 0;
		cin >> n;

		string ip;
		unsigned long long num = 0;

		if (n == 1) {
			cin >> ip;
			ip += ".";
			int val = 0;
			int j = 0;
			for (int i = 0; i < ip.size(); i++) {
				if (ip[i] == '.') {
					num += (unsigned long long)(val * pow(256, 7 - j));
					j++;
					val = 0;
				}
				else {
					int a = ip[i] - '0';
					val = val * 10 + a;
				}
			}
			cout << num << "\n";
		}
		else {
			cin >> num;
			dec2ip(num);
		}
	}
	return 0;
}