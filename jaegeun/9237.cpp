// 이장님 초대
// https://www.acmicpc.net/problem/9237

#include <iostream>
#include <algorithm>

#define MAX 100000

using namespace std;

int N;
int tree[MAX];

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> tree[i];
	}
	sort(tree, tree + N, greater<int>());
	
	int result = 0;
	for (int i = 0; i < N; i++) {
		if (i + tree[i] > result) result = tree[i] + i;
	}
	cout << result + 2 << "\n";
	return 0;
}