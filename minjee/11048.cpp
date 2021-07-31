#include<iostream>
#include<algorithm>
using namespace std;

int arr[1000][1000];
int res[1000][1000];

int solution(int n, int m) {
	res[0][0] = arr[0][0];

	for (int i = 1; i <= n; i++) {
		res[i][0] = res[i - 1][0] + arr[i][0];
	}

	for (int i = 1; i <= m; i++) {
		res[0][i] = res[0][i - 1] + arr[0][i];
	}

	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			res[y][x] = max(res[y - 1][x], res[y][x - 1]) + arr[y][x];
		}
	}
	return res[n][m];
}

int main() {
	int N, M;
	cin >> N >> M;
	int n = N - 1;
	int m = M - 1;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> arr[y][x];
		}
	}
	cout << solution(n, m);

	return 0;

}