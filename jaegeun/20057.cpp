// 마법사 상어와 파이어볼
// https://www.acmicpc.net/problem/20057

#include <iostream>
#include <cmath>

#define MAX 499
using namespace std;

int N = 0;
int out_cnt;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

int board[MAX][MAX];

double percentage[] = { 0.05, 0.1, 0.1, 0.02, 0.07, 0.07, .02, .01, .01 };
//			방향, 축, 순서 
int move_arr[4][2][9]
{	// 0
	{
		{0, -1, 1, -2, -1, 1, 2, -1, 1},
		{-2, -1, -1, 0, 0, 0, 0, 1, 1}
	},
	// 1
	{
		{2, 1, 1, 0, 0, 0, 0, -1, -1},
		{0, -1, 1, -2, -1, 1, 2, -1 ,1}
	},
	// 2
	{
		{0, -1, 1, -2, -1, 1, 2, -1, 1},
		{2, 1, 1, 0, 0, 0, 0, -1, -1}
	},
	{
		{-2, -1, -1, 0, 0, 0, 0, 1, 1},
		{0, -1, 1, -2, -1, 1, 2, -1, 1}
	}	
};

void move_sends(int cx, int cy, int nx, int ny, int d)
{
	int total_send = board[nx][ny];
	int moved = 0; // 이동한 모래
	for (int i = 0; i < 9; i++)
	{
		int send_nx = nx + move_arr[d][0][i];
		int send_ny = ny + move_arr[d][1][i];
		int amount = floor(total_send * percentage[i]);
		if (send_nx < 0 || send_ny < 0 || send_nx >= N || send_ny >= N)
		{
			out_cnt += amount; // 격자 밖으로 나감
		}
		else
		{
			board[send_nx][send_ny] += amount;
		}
		moved += amount; // 움직인 모래 계산
	}
	int remain_send = total_send - moved;
	int remain_x = nx + dx[d];
	int remain_y = ny + dy[d];
	if (remain_x < 0 || remain_y < 0 || remain_x >= N || remain_y >= N)
	{
		out_cnt += remain_send;
	}
	else
	{
		board[remain_x][remain_y] += remain_send;
	}
	board[nx][ny] = 0;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
	
	int cx = N / 2;
	int cy = N / 2;
	int d = 0; // 방향
	int d_cnt = 1;
	int cur = 1;
	board[cx][cy] = cur++;
	while (true)
	{
		for (int cnt = 0; cnt < 2; cnt++) {
			for (int i = 0; i < d_cnt; i++)
			{
				if (cx == 0 && cy == 0) break;
				int nx = dx[d] + cx;
				int ny = dy[d] + cy;
				move_sends(cx, cy, nx, ny, d);

				cx = nx;
				cy = ny;
			}
			d = (d + 1) % 4;
		}
		if (cx == 0 && cy == 0) break;
		d_cnt++;
		
	}
	cout << out_cnt << "\n";
	return 0;
}