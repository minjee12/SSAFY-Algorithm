#include<iostream>
#include<stack>
#include<vector>

using namespace std;

int N, P;
stack<int> s;
int a, b;
vector<int> v[300001];
int cnt = 0;

void func(int n) {
	s.push(v[n][0]);
	cnt++;
	for (int i = 1; i < v[n].size(); i++) {
		while (true) {
			int num = s.top();
			if (v[n][i] < num) {
				s.pop();
				cnt++;
				if (s.empty()) {
					s.push(v[n][i]);
					cnt++;
					break;
				}
			}
			else if (v[n][i] > num) {
				s.push(v[n][i]);
				cnt++;
				break;
			}
			else break;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> P;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		v[a].push_back(b);
	}
	for (int i = 1; i <= P; i++) {
		if (v[i].size() > 0) {
			func(i);
			while (!s.empty()) {
				s.pop();
			}
		}
	}

	cout << cnt;
	return 0;
}