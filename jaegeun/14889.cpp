// 스타트와 링크
// https://www.acmicpc.net/problem/14889

#include <iostream>

#define MAX 21
using namespace std;

int N;
int min_result = 21e8;
int table[MAX][MAX];

int used[21];

int calc_synergy(int flag)
{
	int sum = 0;
	for (int i = 1; i <= N; i++)
	{
		if (used[i] == flag)
		{
			for (int j = 0; j <= N; j++)
			{
				if (i == j) continue;
				if (used[j] == flag) {
					//cout << i << " " << j << " " << table[i][j] << endl;
					sum += table[i][j];
				}
			}
		}
	}
	return sum;
}

void selectTeam(int level, int select)
{
	if(level == N / 2)
	{
		int synergy1 = calc_synergy(1);
		int synergy2 = calc_synergy(0);
		int diff = abs(synergy1 - synergy2);
		if (diff < min_result) min_result = diff;
		return;
	}
	for (int i = select; i <= N; i++)
	{
		if (!used[i]) 
		{
			used[i] = 1;
			selectTeam(level + 1, i + 1);
			used[i] = 0;
		}
	}
}


int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> table[i][j];
		}
	}
	selectTeam(0, 1);
	cout << min_result << endl;
	return 0;
}