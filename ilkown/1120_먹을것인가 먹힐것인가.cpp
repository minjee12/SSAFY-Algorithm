#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

int N, M;
int A[20001] = {};
int B[20001] = {};
//A가 B보다 큰 쌍의 개수

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int tc;

	cin >> tc;

	while (tc--) {

		int ans = 0;
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		cin >> N >> M;

		for (int i = 1; i <= N; i++) cin >> A[i];
		for (int i = 1; i <= M; i++) cin >> B[i];

		//sort(A, A + N + 1);
		sort(B, B + M + 1);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (A[i] > B[j]) ans++;
				else break;
			}
		}
		cout << ans << endl;
	}
	return 0;
}