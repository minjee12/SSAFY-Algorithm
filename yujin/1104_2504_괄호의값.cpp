#include <iostream>
#include <string>
#include <stack>
using namespace std;

stack<char> op;
stack<int> num;

int main() {

	string ss = "";
	cin >> ss;
	for (int i = 0; i < ss.size(); i++) {
		char c = ss[i];
		int flag = 0;
		if (c == ')') {
			int n = 0;
			while (!op.empty()) {
				int tmp = op.top();
				op.pop();
				if (tmp == '(') {
					if (n == 0) num.push(2);
					else num.push(2 * n);
					op.push('n');
					break;
				}
				else if (tmp == '[' || tmp == ']') {
					flag = 1;
				}
				else if (tmp == 'n') {
					n += num.top();
					num.pop();
				}
			}
			if (op.empty()) flag = 1;
		}
		else if (c == ']') {
			int n = 0;
			while (!op.empty()) {
				int tmp = op.top();
				op.pop();
				if (tmp == '[') {
					if (n == 0) num.push(3);
					else num.push(3 * n);
					op.push('n');
					break;
				}
				else if (tmp == '(' || tmp == ')') {
					flag = 1;
				}
				else if (tmp == 'n') {
					n += num.top();
					num.pop();
				}
			}
			if (op.empty()) flag = 1;
		}
		else {
			op.push(c);
		}
		if (flag == 1) {
			cout << 0 << "\n";
			exit(0);
		}
	}

	int res = 0;
	while (!op.empty()) {
		if (op.top() != 'n') {
			cout << 0 << "\n";
			exit(0);
		}
		op.pop();
	}

	while (!num.empty()) {
		res += num.top();
		num.pop();
	}

	cout << res;
	return 0;
}
