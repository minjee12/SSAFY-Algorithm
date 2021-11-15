#include <iostream>

#define MAX 300000
using namespace std;

int arr[200];

int mini = 21e8;
int N;
int n = 0;

void dfs(int lv, int idx, int sum) {
	if (lv >= mini) return;
	if (sum > N) return;
	if (sum == N) {
		mini = (lv < mini) ? lv : mini;
		return;
	}

	for (int i = idx; i >= 0; i--) {
		dfs(lv + 1, i, sum + arr[i]);
	}
}

int main() {
	cin >> N;

	while (1) { // N�� ũ�⿡ ���� ���� �� �ִ� ũ���� ���ü�� arr �迭�� ��� ����
		n++;
		int num = (n * (n + 1) * (2 * n + 1) / 6 + n * (n + 1) / 2) / 2;
		if (num > MAX) break;
		arr[n] = num;
	}

	dfs(0, n - 1, 0); // arr ��Ҹ� ������ ���� �� �ִ� �ּ� ���ü ������ ����

	cout << mini;

	return 0;
}