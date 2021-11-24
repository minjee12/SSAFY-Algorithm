#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int A[20000], B[20000];

int eat(int N, int M) {
	for (int i = 0; i < N; i++) cin >> A[i];
	for (int i = 0; i < M; i++) cin >> B[i];
	sort(A, A + N); sort(B, B + M);

	int cnt = 0;
	
	for (int i = 0; i < N; i++) {
		int start = 0, end = M - 1;
		int center;
		if (A[i] > B[end]) {
			cnt += M;
			continue;
		}
		else if (A[i] < B[start]) {
			continue;
		}
		while (1) {
			center = (start + end) / 2;
			if (start >= end) {
				cnt += start;
				break;
			}

			if (A[i] > B[center]) {
				start = center + 1;
			}
			else if (A[i] <= B[center]) {
				end = center;
			}
		}
	}
	return cnt;
}

int main() {
	int T; cin >> T;

	for (int i = 1; i <= T; i++) {
		int N, M; cin >> N >> M;
		cout << eat(N, M) << "\n";
	}

	return 0;
}