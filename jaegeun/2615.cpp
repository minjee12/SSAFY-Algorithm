// ����
// https://www.acmicpc.net/problem/2615

#include <iostream>
#include <cstring>

#define endl '\n'

#define BLACK 1
#define WHITE 2
#define BLANK 0

#define BOARD_SIZE 19

using namespace std;

int board[BOARD_SIZE][BOARD_SIZE] = { 0, };

//           �� �� ��  ��
int dx[] = {  1, 1, 1, 0 };
int dy[] = { -1, 0, 1, 1};

//		      ��  ��  ��  ��
int rdx[] = { -1, -1, -1,  0};
int rdy[] = {  1,  0, -1, -1};

// �ش� ������ �� ���� ����
int cnt_stone(int x, int y, int direct)
{
	int nx = x + dx[direct];
	int ny = y + dy[direct];
	//cout << "nx : " << nx << ", ny : " << ny << endl;
	int cnt = 1;
	while (true)  // direct ���� Ž��
	{
		// �ε����� ������ �׻� ��������!!
		if (nx < 0 || BOARD_SIZE <= nx || ny < 0 || BOARD_SIZE <= ny) break; // ���� ���
		if (board[nx][ny] != board[x][y]) break;// ���� ĭ�� ���� ���� ���� �ٸ�
		nx = nx + dx[direct];
		ny = ny + dy[direct];
		//cout << "nx : " << nx << ", ny : " << ny << endl;
		cnt++;
	}
	nx = x + rdx[direct];
	ny = y + rdy[direct];
	while (true)  // direct �ݴ� ���� Ž��
	{
		// �ε����� ������ �׻� ��������!!
		if (nx < 0 || BOARD_SIZE <= nx || ny < 0 || BOARD_SIZE <= ny) break; // ���� ���
		if (board[nx][ny] != board[x][y]) break;// ���� ĭ�� ���� ���� ���� �ٸ�
		nx = nx + rdx[direct];
		ny = ny + rdy[direct];
		//cout << "nx : " << nx << ", ny : " << ny << endl;
		cnt++;
	}

	return cnt;
}


int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] != BLANK)
			{
				for (int d = 0; d < 4; d++)
				{
					int result = cnt_stone(i, j, d);
					//cout << i << "," << j << " : " << result << " direction : " << d << endl;
					//cout << board[i][j] << endl;
					if (result == 5) {
						if (d == 0) // �� ���� Ž�� ����ó��
						{
							cout << board[i][j] << endl << i + 5 << " " << j - 3;
						}
						else
						{
							cout << board[i][j] << endl << i + 1 << " " << j + 1;
						}
						exit(0);
					}
				}
			}
		}
	}
	cout << 0;
	return 0;
}