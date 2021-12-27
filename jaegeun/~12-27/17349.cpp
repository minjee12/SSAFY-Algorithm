// 1루수가 누구야
// https://www.acmicpc.net/problem/17349


#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int inp[10][2];
int result[10];

int check(int false_idx) {
	int is_first_baseman[10];
	fill(is_first_baseman, is_first_baseman + 10, -1);
	for (int i = 1; i <= 9; i++) {
		if (i == false_idx) {
			if (inp[i][0] == 1) {
				if (is_first_baseman[inp[i][1]] == -1) is_first_baseman[inp[i][1]] = 0;
				else if (is_first_baseman[inp[i][1]] == 1) return -1; // 모순
			}
			else if (inp[i][0] == 0) {
				if (is_first_baseman[inp[i][1]] == -1) is_first_baseman[inp[i][1]] = 1;
				else if (is_first_baseman[inp[i][1]] == 0) return -1;
			}
		}
		else {
			if (inp[i][0] == 1) {
				if (is_first_baseman[inp[i][1]] == -1) is_first_baseman[inp[i][1]] = 1;
				else if (is_first_baseman[inp[i][1]] == 0) return -1;
			}
			else if (inp[i][0] == 0) {
				if (is_first_baseman[inp[i][1]] == -1) is_first_baseman[inp[i][1]] = 0;
				else if (is_first_baseman[inp[i][1]] == 1) return -1;
			}
		}
	}
	int cnt_unknown = 0;
	int cnt_true = 0;
	for (int i = 1; i <= 9; i++) {
		if (is_first_baseman[i] == 1) cnt_true++;
		if (is_first_baseman[i] == -1) cnt_unknown++;
	}
	if (cnt_true == 1) { // 1루수 한명으로 특정 가능
		for (int i = 1; i <= 9; i++) {
			if (is_first_baseman[i] == 1) return i;
		}
	}
	else if (cnt_unknown == 1 && cnt_true == 0) { // 모르는 사람 1명
		for (int i = 1; i <= 9; i++) {
			if (is_first_baseman[i] == -1) return i;
		}
	}
	else if (cnt_unknown > 1 && cnt_true == 0) { // 모르는 사람이 여러명
		return -2;
	}
	return -1;
}

int main() {
	//ios_base::sync_with_stdio(0); cin.tie(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);

	for (int i = 1; i <= 9; i++) {
		cin >> inp[i][0] >> inp[i][1];
	}

	for (int i = 1; i <= 9; i++) {
		result[i] = check(i);
#ifdef _DEBUG
		cout << result[i] << "\n";
#endif
	}

	int cnt = 0;
	for (int i = 1; i <= 9; i++) {
		if (result[i] > 0) cnt++;
		if (result[i] == -2) {
			cout << -1;
			return 0;
		}
	}
	if (cnt == 1) {
		for (int i = 1; i <= 9; i++) {
			if (result[i] > 0) cout << result[i] << "\n";
		}
	}
	else cout << -1;
	return 0;
}