// 지금 밥이 문제냐
// https://www.acmicpc.net/source/35080019

#include <iostream>
#include <string>

using namespace std;

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int T; cin >> T;
	while (T--) {
		int t;  cin >> t;
		if (t == 1) {
			string ip; cin >> ip;
			unsigned long long num = 0;
			string sub_ip = "";
			for (int i = 0; i < ip.length(); i++) {
				if (ip[i] == '.') {
					int n = stoi(sub_ip);
					num = (num | n) << 8;
					sub_ip = "";
				}
				else {
					sub_ip += ip[i];
				}
			}
			num = (num | stoi(sub_ip));
			cout << num << "\n";
		}
		else {
			unsigned long long num; cin >> num;
			for (int i = 1; i <= 8; i++) {
				unsigned int n = (num >> (64 - (8 * i))) & 0xFF;
				cout << n;
				if (i != 8) cout << ".";
			}
			cout << "\n";
		}
	}
	return 0;
}