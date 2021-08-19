// Two Dots
// https://www.acmicpc.net/problem/16929

#include <iostream>

#define SIZE 50

using namespace std;

int N = 0;
int M = 0;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

char board[SIZE][SIZE] = { 0, };
int board_visited[SIZE][SIZE] = { 0, };

void print_board()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << board_visited[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void dfs(int depth, char color, pair<int, int> pos)
{
	board_visited[pos.first][pos.second] = depth; // 방문 기록 남기기
	//print_board();
	for (int i = 0; i < 4; i++)
	{
		int nx = dx[i] + pos.first;
		int ny = dy[i] + pos.second;

		if (0 <= nx && nx < N && 0 <= ny && ny < M)
		{
			if (board[nx][ny] == color) // 같은 색상일 경우
			{
				// 방문 한경우 방문 숫자 확인
				if (board_visited[nx][ny])
				{
					if (board_visited[nx][ny] < depth - 1)
					{
						cout << "Yes";
						exit(0);
					}
				}
				else {
					dfs(depth + 1, color, make_pair(nx, ny));
				}
			}
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			dfs(1, board[i][j], { i, j });
		}
	}
	cout << "No";
	return 0;
}