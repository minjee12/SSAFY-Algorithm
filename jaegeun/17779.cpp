// 게리맨더링 2
// https://www.acmicpc.net/problem/17779

#pragma warning(disable:4996)

#include <iostream>
#include <queue>

#define MAX 20
using namespace std;

int N;
int JHcity[MAX][MAX];
int mask[MAX][MAX];
bool visited[MAX][MAX];

int min_diff = 21e8;

void fill_mask(int x, int y, int d1, int d2)
{
	memset(mask, 0, sizeof(mask));
	mask[x][y] = 5;
	for (int i = 1; i <= d1; i++) { // ↙ 방향 5 채우기
		mask[x + i][y - i] = 5;
		mask[x + d2 + i][y + d2 - i] = 5;
	}
	for (int i = 1; i <= d2; i++) { // ↘ 방향 5 채우기
		mask[x + i][y + i] = 5;
		mask[x + d1 + i][y - d1 + i] = 5;
	}
	
	for (int i = 1; i < d1 + d2; i++) // 5 내부 채우기
	{
		int flag = false;
		for (int j = 0; j < N; j++) {
			if (flag && mask[x + i][j] == 5) break;
			if (!flag && mask[x + i][j] == 5) flag = true;
			if (!mask[x + i][j] && flag) mask[x + i][j] = 5;
		}
	}
	
	// 주어진 조건 그대로
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (mask[i][j]) continue;
			if (i < x + d1 && j <= y) {
				mask[i][j] = 1;
				continue;
			}
			if (i <= x + d2 && y < j) {
				mask[i][j] = 2;
				continue;
			}
			if (x + d1 <= i && j < y - d1 + d2) {
				mask[i][j] = 3;
				continue;
			}
			mask[i][j] = 4;
		}
	}
	
#ifdef _DEBUG
	printf("x : %d, y : %d, i : %d, j : %d\n", x, y, d1, d2);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << mask[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";
#endif
}

int calc_diff()
{
	int sum[6] = { 0, };
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			sum[mask[i][j]] += JHcity[i][j];
		}
	}
	int pop_max= -21e8;
	int pop_min= 21e8;
	for (int i = 1; i <= 5; i++) {
		pop_max = sum[i] > pop_max ? sum[i] : pop_max;
		pop_min = sum[i] < pop_min ? sum[i] : pop_min;
	}
	return pop_max - pop_min;
}

void split_city(int x, int y)
{
	for (int i = 1; i <= y; i++)
	{
		for (int j = 1; y + j < N; j++)
		{
			if (x + i + j < N) {
				fill_mask(x, y, i, j);
				int result = calc_diff();
				min_diff = result < min_diff ? result : min_diff;
			}
		}
	}
}

int main()
{
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++) {
			cin >> JHcity[i][j];
		}
	}

	for (int i = 0; i < N - 2; i++)
	{
		for (int j = 1; j < N - 1; j++)
		{
			split_city(i, j);
		}
	}

	cout << min_diff << "\n";
	return 0;
}