// N과 M (9)
// https://www.acmicpc.net/problem/15663

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int N, M; cin >> N >> M;
	vector<int> arr(N);
	vector<int> sub_arr(N, 0);

	for (int i = 0; i < N; i++) cin >> arr[i];

	sort(arr.begin(), arr.end());
	do {
		bool flag = true;
		for (int i = 0; i < M; i++) {  // 이전 결과와 비교
			if (arr[i] != sub_arr[i]) {
				flag = false;
				break;
			}
		}
		if (flag) continue;  // 이전 결과와 같으면 continue
		// 다르면 M 자리 까지 출력
		for (int i = 0; i < M; i++) {
			cout << arr[i] << " ";
			sub_arr[i] = arr[i];
		}
		cout << "\n";
	} while (next_permutation(arr.begin(), arr.end()));

	return 0;
}