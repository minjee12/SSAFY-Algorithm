// 두 용액
// https://www.acmicpc.net/problem/2470

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int N; cin >> N;
	vector<int> arr(N);
	for (int i = 0; i < N; i++) cin >> arr[i];

	sort(arr.begin(), arr.end());

	int st = 0, ed = N - 1;
	int min_result = 21e8;
	int result1 = 0, result2 = 0;
	while (true)
	{
		if (st >= ed) break;
		int sum = arr[st] + arr[ed];
		if (min_result > abs(sum))
		{
			min_result = abs(sum);
			result1 = arr[st];
			result2 = arr[ed];
		}
		if (sum == 0) break;
		if (sum < 0) st++;
		else ed--;
	}
	cout << result1 << " " << result2 << endl;
	return 0;
}