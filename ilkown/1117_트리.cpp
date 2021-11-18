#include <iostream>
#include <vector>
using namespace std;

int N;
int tree[51] = {};
int leaf[51] = {};
vector<int> child[51];

void cal_leaf(int cur) {

	if (leaf[cur] == -1) return;
	if (leaf[cur] == 0) {
		leaf[cur] = -1;
		return;
	}
	if (child[cur].size() != 0) {
		leaf[cur] = -1;
		int sz = child[cur].size();

		for (int i = 0; i < sz; i++) {
			cal_leaf(child[cur][i]);
		}
	}
	
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int ans = 0;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> tree[i];
		if (tree[i] != -1) {
			child[tree[i]].push_back(i);
			leaf[tree[i]]++;
		}
	}

	int del;
	cin >> del;

	if (tree[del] == -1) {
		cout << 0 << endl;
		return 0;
	}
	else {

		int sz = child[del].size();
		leaf[tree[del]]--;
		leaf[del] = -1;
		if (sz == 0) {
			for (int i = 0; i < N; i++) {
				if (leaf[i] == 0) ans++;
			}
			cout << ans << endl;
		}
		else {
			for (int i = 0; i < sz; i++) {
				cal_leaf(child[del][i]);
			}

			for (int i = 0; i < N; i++) {
				if (leaf[i] == 0) ans++;
			}
			cout << ans << endl;
		}
	}

	return 0;
}