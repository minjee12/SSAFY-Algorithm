// 로봇
// https://www.acmicpc.net/problem/1726

#include <iostream>
#include <queue>
#include <vector>

#define WALL -1

typedef struct
{
	int x;
	int y;
	int d;
}robot_info;

using namespace std;

int N = 0, M = 0;
robot_info st, ed;

//              동  서  남  북
int dx[] = { 0, 0,  0,  1, -1};
int dy[] = { 0, 1, -1,  0,  0};

int board[100][100] = { 0, };

void print_board()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << board[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "==========================" << endl;
}

// x, y에서 갈 수 있는 방향 반환
vector<int> find_next_dir(int x, int y)
{
	vector<int> nd;
	for (int i = 1; i < 5; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 <= nx && nx < N && 0 <= ny && ny < M)
		{
			if (board[nx][ny] != WALL)
			{
				nd.push_back(i);
			}
		}
	}
	return nd;
}

// 현재 기준 방향에서 다음 방향까지 필요한 명령 개수 반환
int calc_rotate_num(int sd, int nd)
{
	if (sd == nd)
	{
		return 0;
	}
	if (sd == 1) // 동
	{
		if (nd == 2) // 서
			return 2;
		else
			return 1;
	}
	if (sd == 2) // 서
	{
		if (nd == 1) // 동
			return 2;
		else
			return 1;
	}
	if (sd == 3) // 남
	{
		if (nd == 4) // 북
			return 2;
		else
			return 1;
	}
	if (sd == 4) // 북
	{
		if (nd == 3) // 남
			return 2;
		else
			return 1;
	}
}

int bfs()
{
	queue<robot_info> q;
	q.push(st);
	int final_d = 0;
	while (q.size())
	{
		robot_info r_info = q.front();
		q.pop();

		// 갈 수 있는 방향
		vector<int> next_dir = find_next_dir(r_info.x, r_info.y);
		for (int i = 0; i < next_dir.size(); i++)
		{
			for (int j = 1; j <= 3; j++) // go k
			{
				int nx = r_info.x + dx[next_dir[i]] * j;
				int ny = r_info.y + dy[next_dir[i]] * j;
				// 범위 내에서
				if (0 <= nx && nx < N && 0 <= ny && ny < M && board[nx][ny] != WALL)
				{
					// 현재까지의 총 명령어 수
					int cur_cmd = board[r_info.x][r_info.y];
					// 회전에 필요한 명령어 수
					int rotate_cmd = calc_rotate_num(r_info.d, next_dir[i]);
					// 총 명령어 수 = 현재 명령어 + 회전 명령어 + go 명령어
					int total_cmd = cur_cmd + rotate_cmd + 1;
					if (nx == ed.x && ny == ed.y)
					{
						
						int result = total_cmd + calc_rotate_num(next_dir[i], ed.d);
						if (board[nx][ny] == 0)
						{
							board[nx][ny] = result;
						}
						else {
							if (result < board[nx][ny])
							{
								board[nx][ny] = result;
							}
						}
					}
					else if (board[nx][ny] == 0)
					{
						board[nx][ny] = total_cmd;
						q.push({ nx, ny, next_dir[i] });
					}
					else if (board[nx][ny] > total_cmd)
					{
						board[nx][ny] = total_cmd;
						q.push({ nx, ny, next_dir[i] });
					}
				}
			}
		}
	}
	return board[ed.x][ed.y];
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
			if (board[i][j] == 1)
				board[i][j] = WALL;
		}
	}
	cin >> st.x >> st.y >> st.d;
	cin >> ed.x >> ed.y >> ed.d;
	st.x--;
	st.y--;
	ed.x--;
	ed.y--;
	if (st.x == ed.x && st.y == ed.y)
	{
		cout << calc_rotate_num(st.d, ed.d);
		exit(0);
	}
	cout << bfs();
	return 0;
}