// 주사위 굴리기
// https://www.acmicpc.net/problem/14499

#include <iostream>

#define MAX 20

using namespace std;
// 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4     
int dx[] = { 0, 0, 0, -1, 1};
int dy[] = { 0, 1, -1, 0, 0 };
int board[MAX][MAX];

/*
  1
3 0 2
  4
  5
*/


int dice[7];

int N = 0, M = 0;

void rolling_dice(int direction)
{
	if (direction == 1) // 동
	{
		swap(dice[1], dice[3]);
		swap(dice[3], dice[6]);
		swap(dice[4], dice[6]);

	}
	else if (direction == 2) // 서
	{
		swap(dice[1], dice[4]);
		swap(dice[4], dice[6]);
		swap(dice[3], dice[6]);
	}
	else if (direction == 3) // 북
	{
		swap(dice[1], dice[2]);
		swap(dice[2], dice[5]);
		swap(dice[2], dice[6]);
	}
	else // 남
	{
		swap(dice[1], dice[2]);
		swap(dice[1], dice[6]);
		swap(dice[1], dice[5]);
	}
}

int get_dice_num(int pos)
{
	return dice[pos];
}



void set_dice_bottom(int num)
{
	// 바닥면이 0이 아닐 경우 칸에 쓰여있는 숫자 복사
	dice[6] = num;
}

void set_board(int x, int y, int num)
{
	board[x][y] = num;
}

int main()
{
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int fdx, fdy, cmd;
	cin >> N >> M >> fdx >> fdy >> cmd;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < cmd; i++)
	{
		int d; cin >> d;
		// 1. 주사위를 d 방향으로 굴린다.
		int ndx = dx[d] + fdx;
		int ndy = dy[d] + fdy;

		// 범위 밖으로 나갈 경우 명령 무시
		if (ndx < 0 || ndx > N - 1 || ndy < 0 || ndy > M - 1) continue;

		// 주사위 굴리기
		rolling_dice(d);

		// 이동한 칸이 0이면
		if (board[ndx][ndy] == 0)
		{
			// 주사위의 바닥면이 칸에 복사됨
			set_board(ndx, ndy, get_dice_num(6));
		}
		// 0이 아니면
		else 
		{
			set_dice_bottom(board[ndx][ndy]); // 칸에 쓰여있는 수가 주사위 바닥면으로 복사
			board[ndx][ndy] = 0; // 칸의 수는 0
		}
		cout << get_dice_num(1) << '\n';
		fdx = ndx; fdy = ndy;
	}
	return 0;
}