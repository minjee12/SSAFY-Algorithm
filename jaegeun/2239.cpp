// 스도쿠
// https://www.acmicpc.net/problem/2239


#include <iostream>
#include <vector>
#include <cstring>

#define SIZE 9
#define endl '\n'

using namespace std;

vector<pair<int, int>> vect;
bool is_first = true;
int board[SIZE][SIZE] = { 0, };
int min_board[SIZE][SIZE] = { 0, };

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

void comp_board() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] < min_board[i][j]) {
				memcpy(min_board, board, sizeof(board));
				return;
			}
		}
	}
}

void solve(int level)
{
	if (level == vect.size())
	{
		if (is_first) {
			memcpy(min_board, board, sizeof(board));
			is_first = false;
		}
		comp_board();
		return;
	}
	int x = vect[level].first;
	int y = vect[level].second;

	int dat[10] = { 0, };

	for (int i = 0; i < SIZE; i++) {
		dat[board[x][i]] = 1;
	}
	for (int i = 0; i < SIZE; i++) {
		dat[board[i][y]] = 1;
	}
	dat_rect(dat, x, y);

	for (int i = 1; i <= SIZE; i++) {
		if (!dat[i]) {
			// 현재 min_board 결과보다 작은 경우 pass
			if (!is_first && min_board[x][y] > i) { 
				continue;
			}
			else {
				board[x][y] = i;
			}
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
			char c; cin >> c;
			board[i][j] = int(c - '0');
			if (board[i][j] == 0)
			{
				vect.push_back(make_pair(i, j));
			}
		}
	}

	solve(0);
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << min_board[i][j];
		}
		cout << endl;
	}
	return 0;
}