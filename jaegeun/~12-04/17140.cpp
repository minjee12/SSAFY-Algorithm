// 이차원 배열과 연산
// https://www.acmicpc.net/problem/17140

#define MAX 100

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int r, c, k;
int r_cnt = 3;
int c_cnt = 3;
int arr[MAX][MAX];
int num_cnt[MAX * 2];

bool compair(int a, int b) {
	if (num_cnt[a] == num_cnt[b]) {
		return a < b;
	}
	return num_cnt[a] < num_cnt[b];
}

// 모든 행 정렬
void r_operation() {
	for (int i = 0; i < r_cnt; i++) {
		vector<int> sort_vect;
		memset(num_cnt, 0, sizeof(num_cnt));
		for (int j = 0; j < c_cnt; j++) {
			if (arr[i][j] > 0) {
				if (num_cnt[arr[i][j]] == 0) sort_vect.push_back(arr[i][j]);
 				num_cnt[arr[i][j]]++;
			}
		}
		sort(sort_vect.begin(), sort_vect.end(), compair);
		memset(arr[i], 0, sizeof(arr[i]));
		for (int j = 0; j < sort_vect.size(); j++) {
			if (j * 2 > 100) break;
			arr[i][2 * j] = sort_vect[j];
			arr[i][2 * j + 1] = num_cnt[sort_vect[j]];
		}
		c_cnt = min(max(c_cnt, int(sort_vect.size() * 2)), 100);
	}
}

// 모든 열 정렬
void c_operation() {
	for (int i = 0; i < c_cnt; i++) {
		vector<int> sort_vect;
		memset(num_cnt, 0, sizeof(num_cnt));
		for (int j = 0; j < r_cnt; j++) {
			if (arr[j][i] > 0) {
				if (num_cnt[arr[j][i]] == 0) sort_vect.push_back(arr[j][i]);
				num_cnt[arr[j][i]]++;
			}
		}
		sort(sort_vect.begin(), sort_vect.end(), compair);
		for (int j = 0; j < 100; j++) arr[j][i] = 0;
		for (int j = 0; j < sort_vect.size(); j++) {
			if (j * 2 > 100) break;
			arr[2 * j][i] = sort_vect[j];
			arr[2 * j + 1][i] = num_cnt[sort_vect[j]];
		}
		r_cnt = min(max(r_cnt, int(sort_vect.size() * 2)), 100);
	}
}

void solve() {
	int t = 0;
	while (true) {
		if (t > 100) {
			cout << -1;
			return;
		}
		if (arr[r - 1][c - 1] == k) {
			cout << t;
			return;
		}
		if (r_cnt >= c_cnt) r_operation();
		else c_operation();
		t++;
	}
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> r >> c >> k;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> arr[i][j];
		}
	}
	solve();
	
	return 0;
}