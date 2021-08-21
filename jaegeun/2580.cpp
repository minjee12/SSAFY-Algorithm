// 스도쿠
// https://www.acmicpc.net/problem/2580

#include <iostream>
#include <vector>

#define SIZE 9
#define endl '\n'

using namespace std;

vector<pair<int, int>> vect;

int board[SIZE][SIZE] = { 0, };

void print_board()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

// 사각형 범위 확인
void dat_rect(int dat[10], int x, int y)
{
	int x_quo = x / 3;
	int y_quo = y / 3;

	//cout << x_quo << " " << y_quo << endl;
	for (int i = x_quo * 3; i < (x_quo * 3) + 3; i++)
	{
		for (int j = y_quo * 3; j < (y_quo * 3) + 3; j++)
		{
			dat[board[i][j]] = 1;
		}
	}
}

void solve(int level)
{
	if (level == vect.size())
	{
		print_board();
		exit(0);
	}
	int dat[10] = { 0, };

	int x = vect[level].first;
	int y = vect[level].second;
	
	// 1. 가로 확인
	for (int i = 0; i < 9; i++) {
		// cout << board[x][i] << " ";
		dat[board[x][i]] = 1;
	}
	// 2. 세로 확인
	for (int i = 0; i < 9; i++) {
		// cout << board[i][y] << " ";
		dat[board[i][y]] = 1;
	}
	// 3. 사각형 범위 확인
	dat_rect(dat, x, y);

	for (int i = 1; i < 10; i++)
	{
		// dat에 없는 문자만 탐색
		if (dat[i] == 0)
		{
			dat[i] = 1;
			board[x][y] = i;
			solve(level + 1);
			board[x][y] = 0;
		}
	}
		
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cin >> board[i][j];

			if (board[i][j] == 0)
			{
				vect.push_back(make_pair(i, j));
			}
		}
	}

	solve(0);
	return 0;
}