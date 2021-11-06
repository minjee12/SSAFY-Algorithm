#include <iostream>
#include <deque>
#include <vector>
using namespace std;

deque<pair<int, int> > dq; //{풍선번호, 종이}
vector<int> res;

int main() {
	//input
	int n = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x = 0;
		cin >> x;
		dq.push_back({ i,x });
	}
	

	while (1) {
		//다음에 터트릴 풍선이 dq의 front에 있도록
		int e = dq.front().second;
		res.push_back(dq.front().first);

		dq.pop_front();
		if (dq.empty()) break;

		if (e > 0) {
			for (int i = 1; i < e; i++) {
				int idx = dq.front().first;
				int num = dq.front().second;
				dq.pop_front();
				dq.push_back({idx, num});
			}
		}
		else {
			for (int i = 0; i < abs(e); i++) {
				int idx = dq.back().first;
				int tmp = dq.back().second;
				dq.pop_back();
				dq.push_front({idx, tmp});
			}
		}
	}

	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	cout << "\n";

	return 0;
}