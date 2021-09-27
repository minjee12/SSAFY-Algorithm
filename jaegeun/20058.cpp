// 마법사 상어와 파이어스톰
// https://www.acmicpc.net/problem/20058

#include <iostream>
#include <vector>
#include <queue>
#define MAX_SIZE 64
#define MAX_Q 1001

using namespace std;

int n = 0, q = 0;
int board_size = 1;
int board[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int stage[MAX_Q];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

// 지수 계산
int get_width(int exp) 
{
	int result = 1;
	for (int i = 0; i < exp; i++) result *= 2;
	return result;
}

void rotate_board(int x, int y, int size, int t_size)
{
	if (size == t_size)
	{
		vector<vector<int>> temp(t_size, vector<int>(t_size));
		int cnt = 1; 
		for (int i = 0; i < t_size; i++)
		{
			for (int j = 0; j < t_size; j++)
			{
				temp[i][j] = board[x + i][y + j];
			}
		}
		// 90도 회전
		int temp_x = 0;
		for (int i = t_size - 1; i >= 0; i--)
		{
			int temp_y = 0;
			for (int j = 0; j < t_size; j++)
			{
				board[x + j][y + i] = temp[temp_x][temp_y++];
			}
			temp_x++;
		}
		return;
	}
	else
	{
		rotate_board(x, y, size / 2, t_size);
		rotate_board(x, y + (size / 2), size / 2, t_size);
		rotate_board(x + (size / 2), y, size / 2, t_size);
		rotate_board(x + (size / 2), y + (size / 2), size / 2, t_size);
	}
}

// 얼음 녹는지 확인
bool is_melt(int x, int y)
{
	int ice_cnt = 0;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 0 || ny < 0 || nx >= board_size || ny >= board_size) continue;
		if (board[nx][ny]) ice_cnt++;
	}
	if (ice_cnt >= 3) return false;
	else return true;
}

void melt()
{
	bool mask[MAX_SIZE][MAX_SIZE] = { 0, };
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			mask[i][j] = is_melt(i, j);
		}
	}
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (mask[i][j] && board[i][j] > 0) board[i][j]--;
		}
	}
}

int get_ice_size(int x, int y)
{
	queue<pair<int, int>> q;
	q.push({ x, y });
	int cnt = 0;
	while (q.size())
	{
		int cx = q.front().first;
		int cy = q.front().second;

		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx < 0 || ny < 0 || nx >= board_size || ny >= board_size) continue;
			if (!visited[nx][ny] && board[nx][ny] > 0) {
				cnt++;
				visited[nx][ny] = true;
				q.push({ nx, ny });
			}
		}
	}
	return cnt;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> n >> q;

	board_size = get_width(n);

	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < q; i++)
	{
		cin >> stage[i];
	}

	for (int i = 0; i < q; i++)
	{
		rotate_board(0, 0, board_size, get_width(stage[i]));
		melt();
	}

	int total_ice = 0;
	int max_result = 0;
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			total_ice += board[i][j];
			if (!visited[i][j]) {
				int result = get_ice_size(i, j);
				max_result = result > max_result ? result : max_result;
			}
		}
	}

	cout << total_ice << "\n" << max_result << "\n";
	return 0;
}