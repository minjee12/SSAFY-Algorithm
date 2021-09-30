// 피보나치
// https://www.acmicpc.net/problem/9009

#include <iostream>
#include <vector>

using namespace std;

int dp[100];

int get_max_index(int num)
{
	int index = 1;
	while (1)
	{
		if (dp[index + 1] > num) return index;
		index++;
	}
}

int main()
{
	dp[1] = 1;
	dp[2] = 1;
	
	int index = 3;
	while (1)
	{
		dp[index] = dp[index - 1] + dp[index - 2];
		if (dp[index] > 1000000000) break;
		index++;
	}
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int num; cin >> num;
		vector<int> sol;
		while (1)
		{
			if (num == 0) break;
			int max_index = get_max_index(num);
			sol.push_back(dp[max_index]);
			num -= dp[max_index];
		}
		for (int i = sol.size() - 1; i >= 0; i--)
		{
			cout << sol[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}