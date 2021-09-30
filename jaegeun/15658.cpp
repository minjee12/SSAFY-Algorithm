// 연산자 끼워넣기(2)
// https://www.acmicpc.net/problem/15658

#include <iostream>

using namespace std;

int max_result = -21e8;
int min_result = 21e8;

int N;
// +, -, x, ÷
int opt_cnt[4];
int nums[11];

int calc_num(int opt, int value_front, int value_back)
{
	if (opt == 0) return value_front + value_back;
	if (opt == 1) return value_front - value_back;
	if (opt == 2) return value_front * value_back;
	if (opt == 3) return value_front / value_back;
}

void dfs(int level, int result)
{
	if (level == N)
	{
		max_result = result > max_result ? result : max_result;
		min_result = result < min_result ? result : min_result;
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		if (opt_cnt[i]) {
			opt_cnt[i]--;
			dfs(level + 1, calc_num(i, result, nums[level]));
			opt_cnt[i]++;
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> nums[i];
	}
	for (int i = 0; i < 4; i++)
	{
		cin >> opt_cnt[i];
	}
	dfs(1, nums[0]);
	cout << max_result << "\n" << min_result;
	return 0;
}