// N과 M (7)
// https://www.acmicpc.net/problem/15656

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 8
using namespace std;

int M = 0, N = 0;

int element[MAX];
int used[MAX];

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

		used[level] = element[i];
		dfs(level + 1);

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