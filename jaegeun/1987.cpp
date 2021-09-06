// 알파벳
// https://www.acmicpc.net/problem/1987

#include <iostream>

#define MAX 20
using namespace std;


int R = 0, C = 0;
int max_cnt = 0;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

char board[MAX][MAX];
int used[26];



void dfs(int x, int y, int count)
{
	bool flag = false;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || nx > R - 1 || ny < 0 || ny > C - 1)continue;
		if (used[board[nx][ny] - 'A']) continue;
		flag = true;
		used[board[nx][ny] - 'A'] = 1;
		dfs(nx, ny, count + 1);
		used[board[nx][ny] - 'A'] = 0;
	}
	if (!flag) max_cnt = max_cnt < count ? count : max_cnt;
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(false);
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> R >> C;

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> board[i][j];
		}
	}
	used[board[0][0] - 'A'] = 1;
	dfs(0, 0, 1);
	cout << max_cnt << '\n';
	return 0;
}