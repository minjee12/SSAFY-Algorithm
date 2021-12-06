#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
bool comp(string front, string back) {
	return front > back;
}

int hextodec(string s) {
	int num = 0;
	int res = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		int tmp = 0;
		if ('A' <= s[i] && s[i] <= 'F') {
			tmp = s[i] - 55;
		}
		else tmp = s[i] - '0';
		res += tmp * pow(16, num);
		num++;
	}
	return res;
}

int main() {

	int test_case = 0;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++) {
		cin >> n >> k;
		string pw = "";
		cin >> pw;

		vector<string> v;

		for (int i = 0; i < n/4; i++) {
			char tmp = pw[n - 1];
			for (int j = n-2; j >= 0; j--) {
				pw[j + 1] = pw[j];
			}
			pw[0] = tmp;

			for (int j = 0; j < n; j = j + n/4) {
				string sub = pw.substr(j, n / 4);
				v.push_back(sub);
			}
		}

		sort(v.begin(), v.end(), comp);
		v.erase(unique(v.begin(), v.end()), v.end());
		
		cout << "#" << t << " " << hextodec(v[k - 1]) << "\n";
	}
	
	return 0;
}
