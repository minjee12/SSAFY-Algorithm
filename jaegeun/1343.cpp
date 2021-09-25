// 폴리오미노
// https://www.acmicpc.net/problem/1343

#include <iostream>
#include <cstring>

#define MAX 501
using namespace std;

char board[MAX];

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	string board; cin >> board;
	string before[2] = { "XXXX", "XX" };
	string pol[2] = { "AAAA", "BB" };
	for (int i = 0; i < 2; i++) {
		int board_ptr = 0;
		while (board_ptr < board.length()) {
			board_ptr = board.find(before[i], board_ptr);
			if (board_ptr == string::npos) break;
			board.replace(board_ptr, before[i].length(), pol[i]);
			board_ptr += pol[i].length();
		}
	}
	for (int i = 0; i < board.length(); i++)
	{
		if (board[i] == 'X') {
			cout << -1 << "\n";
			return 0;
		}
	}
	cout << board << "\n";

	return 0;
};