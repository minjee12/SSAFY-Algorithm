#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int test_case;
vector<int> A;
vector<int> B;

int main() {

	cin >> test_case;
	for (int t = 1; t <= test_case; t++) {
		int a = 0, b = 0;
		cin >> a >> b;
		A.clear();
		B.clear();
		for (int i = 0; i < a; i++) {
			int x = 0;
			cin >> x;
			A.push_back(x);
		}
		for (int i = 0; i < b; i++) {
			int x = 0;
			cin >> x;
			B.push_back(x);
		}
		sort(B.begin(), B.end());
		int cnt = 0;
		for (int i = 0; i < A.size(); i++) {
			for (int j = 0; j < B.size(); j++) {
				if (A[i] > B[j]) cnt++;
				else break;
			}
		}

		cout << cnt << "\n";

	}
	return 0;
}