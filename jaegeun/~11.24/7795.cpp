// 먹을 것인가 먹힐 것인가
// https://www.acmicpc.net/problem/7795

#include <iostream>
#include <algorithm>

#define MAX 20000

using namespace std;

int arrA[MAX];
int arrB[MAX];

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int T; cin >> T;
	for (int t = 0; t < T; t++) {
		int N, M; cin >> N >> M;
		int cnt = 0;
		for (int i = 0; i < N; i++) cin >> arrA[i];
		for (int i = 0; i < M; i++) cin >> arrB[i];

		sort(arrB, arrB + M);

		for (int i = 0; i < N; i++) {
			if (arrA[i] > arrB[M - 1]) cnt += M;
			else {
				for (int j = 0; j < M; j++) {
					if (arrA[i] <= arrB[j]) {
						/*cout << arrA[i] << " , " << arrB[j] << "\n";
						cout << j << "\n";*/
						cnt += j;
						break;
					}
				}
			}
		}
		cout << cnt << "\n";
	}
	return 0;
}
