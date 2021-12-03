#include <memory.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int r, c, k;
int arr[101][101] = {};
int row_cnt = 3;
int col_cnt = 3;
int ans = -1;
int num[101] = {};

struct Node {
	int num;
	int cnt;
};

vector<Node> vec;

int cmp(Node front, Node back) {
	if (front.cnt == back.cnt) {
		return front.num < back.num;
	}
	else return front.cnt < back.cnt;
}

void R(int y, int x) {
	int temp[101][101] = {};
	int x_cnt = 1;
	int max_cnt = -9999999999;
	for (int i = 1; i <= y; i++) {
		memset(num, 0, sizeof(num));
		vec.clear();
		for (int j = 1; j <= x; j++) {
			if (arr[i][j] != 0) {
				num[arr[i][j]]++;
			}
		}
		for (int j = 1; j <= 100; j++) {
			if (num[j] != 0) {
				vec.push_back({ j,num[j] });
			}
		}
		sort(vec.begin(), vec.end(), cmp);

		int sz = vec.size();

		for (int j = 0; j < sz; j++) {
			temp[i][x_cnt++] = vec[j].num;
			temp[i][x_cnt] = vec[j].cnt;
			x_cnt++;
		}
		x_cnt--;
		if (max_cnt < x_cnt) max_cnt = x_cnt;
		x_cnt = 1;
	}
	memcpy(arr, temp, sizeof(temp));

	row_cnt = y;
	col_cnt = max_cnt;
}

void C(int y, int x) {
	int temp[101][101] = {};
	int y_cnt = 1;
	int max_cnt = -9999999999;

	for (int i = 1; i <= x; i++) {
		memset(num, 0, sizeof(num));
		vec.clear();
		for (int j = 1; j <= y; j++) {
			if (arr[j][i] != 0) {
				num[arr[j][i]]++;
			}
		}
		for (int j = 1; j <= 100; j++) {
			if (num[j] != 0) {
				vec.push_back({ j,num[j] });
			}
		}
		sort(vec.begin(), vec.end(), cmp);

		int sz = vec.size();

		for (int j = 0; j < sz; j++) {
			temp[y_cnt++][i] = vec[j].num;
			temp[y_cnt][i] = vec[j].cnt;
			y_cnt++;
		}
		y_cnt--;
		if (max_cnt < y_cnt) max_cnt = y_cnt;
		y_cnt = 1;
	}

	memcpy(arr, temp, sizeof(temp));

	row_cnt = max_cnt;
	col_cnt = x;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> r >> c >> k;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> arr[i][j];
		}
	}

	if (arr[r][c] == k) {
		cout << "0\n";
		return 0;
	}

	for (int i = 1; i <= 100; i++) {
		
		if (row_cnt >= col_cnt) R(row_cnt, col_cnt);
		else C(row_cnt, col_cnt);

		if (arr[r][c] == k) {
			ans = i;
			break;
		}

	}

	cout << ans << "\n";

	return 0;
}