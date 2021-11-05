// 괄호의 값
// https://www.acmicpc.net/problem/2504

#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);

	string str; cin >> str;

	deque<char> q;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(' || str[i] == '[') {
			q.push_back(str[i]);
		}
		else if (str[i] == ')') {
			if (!q.size()) {
				cout << 0;
				return 0;
			}
			if (q[q.size() - 1] == '(') {
				q.pop_back();
			}
		}
		else if (str[i] == ']') {
			if (!q.size()) {
				cout << 0;
				return 0;
			}
			if (q[q.size() - 1] == '[') {
				q.pop_back();
			}
		}
	}
	if (q.size() == 0) {
		int result = 0;
		int temp = 1;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == '(') {
				temp *= 2;
				q.push_back('(');
			}
			if (str[i] == '[') {
				temp *= 3;
				q.push_back('[');
			}
			if (str[i] == ')') {
				if (str[i - 1] == '(')
					result += temp;
				temp /= 2;
				q.pop_back();
			}
			if (str[i] == ']') {
				if (str[i - 1] == '[')
					result += temp;
				temp /= 3;
				q.pop_back();
			}
			cout << temp << ", " << result << "\n";
		}
		cout << result << "\n";
	}
	else {
		cout << 0;
	}
	return 0;
}