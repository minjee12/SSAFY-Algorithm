// 마법사 상어와 파이어볼
// https://www.acmicpc.net/problem/20056

#include <iostream>
#include <vector>
#include <cstring>

#define MAX 50

using namespace std;

typedef struct {
	int m;
	int s;
	int d;
}fireball;

int N, M, K;

int dx[] = { -1, -1, 0, 1, 1,  1,  0, -1 };
int dy[] = {  0,  1, 1, 1, 0, -1 ,-1, -1 };
vector<fireball> board[MAX][MAX];


bool get_next_directions(int x, int y)
{
	int first_direction = board[x][y][0].d % 2;
	
	for (int i = 1; i < board[x][y].size(); i++)
	{
		int next_direction = board[x][y][i].d % 2;
		if (first_direction != next_direction) return false;
	}
	return true; // 방향이 모두 짝수거나 홀수임
}

void spread_fireball()
{
	vector<fireball> temp[MAX][MAX];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (auto x : board[i][j])
			{
				int nx = (i + ((dx[x.d] * x.s) % N)) % N;
				int ny = (j + ((dy[x.d] * x.s) % N)) % N;

				if (nx < 0) nx += N;
				if (ny < 0) ny += N;
				temp[nx][ny].push_back({ x.m, x.s, x.d });
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			board[i][j] = temp[i][j];
		}
	}
}

void after_spread()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (board[i][j].size() > 1)
			{
				int cnt = board[i][j].size();
				int total_mass = 0;
				int total_speed = 0;

				for (auto x : board[i][j])
				{
					total_mass += x.m;
					total_speed += x.s;
				}
				bool directions = get_next_directions(i, j);
				board[i][j].clear();
				int next_mass = total_mass / 5;
				if (next_mass > 0) {
					int next_speed = total_speed / cnt;
					if (directions)
					{
						for (int d = 0; d < 4; d++)
						{
							board[i][j].push_back({ next_mass, next_speed, d * 2 });
						}
					}
					else
					{
						for (int d = 0; d < 4; d++)
						{
							board[i][j].push_back({ next_mass, next_speed, d * 2 + 1 });
						}
					}
				}
					
			}
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++)
	{
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		board[r - 1][c - 1].push_back({ m, s, d });
	}
	for (int i = 0; i < K; i++) {
		spread_fireball();
		after_spread();
	}
	
	int result = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (auto x : board[i][j])
			{
				result += x.m;
			}
		}
	}
		cout << result << "\n";
	return 0;
}