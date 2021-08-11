// 연구소
// https://www.acmicpc.net/problem/14502

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

#define SIZE 8 + 1
#define EMPTY 0
#define WALL 1
#define VIRUS 2

using namespace std;

int N = 0, M = 0;
int cnt = 0;

int max_safe_area = 0;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int lab[SIZE][SIZE] = { 0, };
int lab_copy[SIZE][SIZE] = { 0, };
int lab_visited[SIZE][SIZE] = { 0, };
void spread(int x, int y)
{
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	lab_visited[x][y] = 1;
	lab_copy[x][y] = 2;

	while (q.size())
	{
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (0 <= nx && nx < N && 0 <= ny && ny < M)
			{
				if (!lab_visited[nx][ny] && lab_copy[nx][ny] == 0)
				{
					q.push(make_pair(nx, ny));
					lab_copy[nx][ny] = 2;
					lab_visited[nx][ny] = 1;
				}
			}
		}
	}
}

int cnt_safe_area()
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (lab_copy[i][j] == 0) cnt++;
		}
	}
	return cnt;
}

void mk_wall(int level)
{
	if (level == 3)
	{
		memcpy(lab_copy, lab, sizeof(lab));
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (lab_copy[i][j] == 2 && !lab_visited[i][j])
				{
					spread(i, j);
				}
			}
		}
		max_safe_area = max(cnt_safe_area(), max_safe_area);
		memset(lab_visited, 0, sizeof(lab_visited)); // 방문 기록 초기화
		return;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (lab[i][j] == 0)
			{
				lab[i][j] = 1;
				mk_wall(level + 1);
				lab[i][j] = 0;
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
			cin >> lab[i][j];
		}
	}
	
	mk_wall(0);
	cout << max_safe_area;
	return 0;
}