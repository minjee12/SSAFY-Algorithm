#include <iostream>
#include <stack>
using namespace std;


int main() {

	stack<int> guitar[7];

	int N, P;
	int cnt = 0;

	cin >> N >> P;

	for (int i = 0; i < N; i++) {
		int str, flat;
		cin >> str >> flat;

		if (guitar[str].empty()) {
			guitar[str].push(flat);
			cnt++;
		}
		else {
			if (guitar[str].top() < flat) {
				guitar[str].push(flat);
				cnt++;
			}
			else if (guitar[str].top() == flat) continue;

			else if (guitar[str].top() > flat) {
				while (1) {
					if (guitar[str].empty())break;
					if (guitar[str].top() <= flat) break;
					guitar[str].pop();
					cnt++;
				}
				if (guitar[str].size() >=1 && guitar[str].top() == flat) continue;
				guitar[str].push(flat);
				cnt++;
			}
		}
	}

	cout << cnt << endl;
	return 0;
}