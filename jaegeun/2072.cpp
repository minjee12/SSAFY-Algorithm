// ����
// https://www.acmicpc.net/problem/2072

#include <iostream>
#include <algorithm>
#include <queue>

#define endl '\n'

#define BOARD_SIZE 19
#define BLACK 1
#define WHITE 2

using namespace std;

int M = 0;

queue<pair<int, int>> SD; // ����
queue<pair<int, int>> GM; // ������

//			 ��  ��  �� ��   ��  ��  �� ��
int dx[] = { -1, -1,  1, 1 , -1, 1,  0, 0 };
int dy[] = { -1,  1, -1 ,1 ,  0, 0, -1, 1 };

// �ݴ����  �� ��  ��  ��    ��  ��  ��  ��
int rdx[] = { 1,  1, -1, -1 ,  1, -1,  0,  0 };
int rdy[] = { 1, -1,  1 ,-1 ,  0,  0,  1, -1 };

int board[BOARD_SIZE + 1][BOARD_SIZE + 1] = { 0, };

// �ش� ��ġ���� ���⿡ ���� ���� �� �� ����
int cnt_color(int x, int y, int d)
{
	int cnt = 1; // ���� ���� �� ����, �ڱ� �ڸ� 1����
	int nx = x + dx[d];
	int ny = y + dy[d];

	while (true) // ������ Ž��
	{
		if (nx < 0 || BOARD_SIZE <= nx || ny < 0 || BOARD_SIZE <= ny) break; // ���� �ƿ�
		if (board[nx][ny] != board[x][y]) break; // ���� �ٸ�
		cnt++;
		nx = nx + dx[d];
		ny = ny + dy[d];
	}
	nx = x + rdx[d];
	ny = y + rdy[d];

	while (true) // ������ Ž��
	{
		if (nx < 0 || BOARD_SIZE <= nx || ny < 0 || BOARD_SIZE <= ny) break; // ���� �ƿ�
		if (board[nx][ny] != board[x][y]) break; // ���� �ٸ�
		cnt++;
		nx = nx + rdx[d];
		ny = ny + rdy[d];
	}
	return cnt;
}

int main()
{
	cin >> M; // �Է� ����, K ��

	int x, y;
	for (int i = 0; i < M; i++)
	{
		cin >> x >> y;
		if (i % 2 == 0) // ��
		{
			board[x][y] = BLACK;
		}
		else
		{
			board[x][y] = WHITE;
		}
		for (int d = 0; d < 8; d++)
		{
			int result = cnt_color(x, y, d);
			if (result == 5)
			{
				cout << i + 1 << endl;
				exit(0);
			}
		}
	}

	cout << -1;
	return 0;
}