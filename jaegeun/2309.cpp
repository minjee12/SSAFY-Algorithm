// 일곱 난쟁이
// https://www.acmicpc.net/problem/2309

#include <iostream>
#include <algorithm>
using namespace std;

int height[9];
bool used[9];
int memo[7];

void find(int level, int index)
{
	if (level == 7) {
		int sum = 0;
		for (int i = 0; i < 7; i++)
		{
			sum += memo[i];
		}
		if (sum == 100)
		{
			for (int i = 0; i < 7; i++)
			{
				cout << memo[i] << "\n";
 			}
			exit(0);
		}
		return;
	}
	for (int i = index; i < 9; i++) {
		if (used[i]) continue;
		memo[level] = height[i];
		used[i] = true;
		find(level + 1, index + 1);
		used[i] = false;
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	for (int i = 0; i < 9; i++)
	{
		cin >> height[i];
	}
	sort(height, height + 9);
	find(0, 0);
	return 0;
}