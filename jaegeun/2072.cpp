// 오목
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

queue<pair<int, int>> SD; // 세돌
queue<pair<int, int>> GM; // 감마고

//			 ↖  ↗  ↙ ↘   상  하  좌 우
int dx[] = { -1, -1,  1, 1 , -1, 1,  0, 0 };
int dy[] = { -1,  1, -1 ,1 ,  0, 0, -1, 1 };

// 반대방향  ↘ ↙  ↗  ↖    하  상  우  좌
int rdx[] = { 1,  1, -1, -1 ,  1, -1,  0,  0 };
int rdy[] = { 1, -1,  1 ,-1 ,  0,  0,  1, -1 };

int board[BOARD_SIZE + 1][BOARD_SIZE + 1] = { 0, };

// 해당 위치부터 방향에 놓인 같은 색 돌 세기
int cnt_color(int x, int y, int d)
{
	int cnt = 1; // 같은 색깔 돌 개수, 자기 자리 1부터
	int nx = x + dx[d];
	int ny = y + dy[d];

	while (true) // 정방향 탐색
	{
		if (nx < 0 || BOARD_SIZE <= nx || ny < 0 || BOARD_SIZE <= ny) break; // 범위 아웃
		if (board[nx][ny] != board[x][y]) break; // 색깔 다름
		cnt++;
		nx = nx + dx[d];
		ny = ny + dy[d];
	}
	nx = x + rdx[d];
	ny = y + rdy[d];

	while (true) // 역방향 탐색
	{
		if (nx < 0 || BOARD_SIZE <= nx || ny < 0 || BOARD_SIZE <= ny) break; // 범위 아웃
		if (board[nx][ny] != board[x][y]) break; // 색깔 다름
		cnt++;
		nx = nx + rdx[d];
		ny = ny + rdy[d];
	}
	return cnt;
}

int main()
{
	cin >> M; // 입력 개수, K 목

	int x, y;
	for (int i = 0; i < M; i++)
	{
		cin >> x >> y;
		if (i % 2 == 0) // 흑
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