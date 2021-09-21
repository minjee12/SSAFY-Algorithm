// N과 M (5)
// https://www.acmicpc.net/problem/15654

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 8
using namespace std;

int M = 0, N = 0;

int element[MAX];
int used[MAX];

bool is_used(int ele, int used_size)
{
	for (int i = 0; i < used_size; i++)
	{
		if (used[i] == ele) return true;
	}
	return false;
}

void dfs(int level)
{
	if (level == M)
	{
		for (int i = 0; i < M; i++)
		{
			cout << used[i] << " ";
		}
		cout << "\n";
		return;
	}
	for (int i = 0; i < N; i++)
	{
		if (!is_used(element[i], level))
		{
			used[level] = element[i];
			dfs(level + 1);
		}
	}
}

int main()
{
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		cin >> element[i];
	}
	sort(element, element + N);
	dfs(0);
}