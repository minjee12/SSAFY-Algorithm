#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, int> set;
int n, m;

int main() {

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string str;
		cin >> str;
		set[str] = 1;
	}

	int res = 0;
	for (int i = 0; i < m; i++) {
		string arr;
		cin >> arr;
		if (set[arr] == 1) res++;
	}
	cout << res << "\n";
	return 0;
}