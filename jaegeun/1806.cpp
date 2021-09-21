#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr[100001];
int dat[10001];

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	int n, s; cin >> n >> s;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) cin >> arr[i];

	int result = 0;

	int sum = arr[0];
	int st = 0; int ed = 0;
	while (true)
	{
		if (st == n) break;
		if (sum < s) // 부분 합이 s보다 작을 때
		{
			// ed가 마지막지점에 도착했을 때 부분 합이 s보다 작으면 더 이상 탐색할 필요 x
			if (ed == n - 1) break; 
			ed++;
			sum += arr[ed];
		}
		else if (sum >= s)
		{
			int length = ed - st + 1;
			if (result == 0 || result > length)
			{
				result = length;
			}
			sum -= arr[st];
			st++;
		}
	}
	cout << result << endl;
	return 0;
}