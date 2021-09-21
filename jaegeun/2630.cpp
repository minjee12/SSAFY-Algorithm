// 색종이 만들기
// https://www.acmicpc.net/problem/2630

#include <iostream>
#define MAX 128


using namespace std;


int board[MAX][MAX];

int cnt_blue = 0;
int cnt_white = 0;

void calc(int x, int y, int size)
{
	if (size == 1)
	{
		if (board[x][y]) cnt_blue++;
		else cnt_white++;
		return;
	}
	int stand = board[x][y];
	bool flag = true; // 색이 모두 같다고 가정
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[x + i][y + j] != stand)
			{
				flag = false;
			}
		}
	}
	if (flag) {
		if (stand) cnt_blue++;
		else cnt_white++;
		return;
	}
	else {
		int next_size = size / 2;
		calc(x, y, next_size);
		calc(x + next_size, y, next_size);
		calc(x, y + next_size, next_size);
		calc(x + next_size, y + next_size, next_size);
	}
}

int main()
{
	cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int n = 0; cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> board[i][j];
		}
	}
	calc(0, 0, n);
	cout << cnt_white << '\n' << cnt_blue << '\n';
	return 0;
}