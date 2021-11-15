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

	while (1) { // N의 크기에 따라 나올 수 있는 크기의 사면체를 arr 배열에 모두 저장
		n++;
		int num = (n * (n + 1) * (2 * n + 1) / 6 + n * (n + 1) / 2) / 2;
		if (num > MAX) break;
		arr[n] = num;
	}

	dfs(0, n - 1, 0); // arr 요소를 조합해 나올 수 있는 최소 사면체 개수를 구함

	cout << mini;

	return 0;
}