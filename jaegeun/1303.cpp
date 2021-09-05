// 전쟁 - 전투
// https://www.acmicpc.net/problem/1303

#include <iostream>
#include <queue>

#define MAX 100

using namespace std;

int N = 0, M = 0;

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

char field[MAX][MAX];
int visited[MAX][MAX];



int bfs(int x, int y, char team)
{
	queue<pair<int, int>> q;
	q.push({ x, y });
	
	visited[x][y] = 1;

	int cnt = 1;
	while (q.size())
	{
		int cx = q.front().first;
		int cy = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) continue;
			if (visited[nx][ny]) continue;
			if (field[nx][ny] != team) continue;
			visited[nx][ny] = 1;
			q.push({ nx, ny });
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	// 전쟁터의 가로 크기 N, 세로 크기 M(1 ≤ N, M ≤ 100)이 주어진다.!!!!
	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> field[i][j];
		}
	}
	int f_cnt = 0;
	int a_cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (!visited[i][j])
			{
				int result = bfs(i, j, field[i][j]);
				cout << field[i][j] << " " << result << '\n';
				if (field[i][j] == 'W') f_cnt += result * result;
				else a_cnt += result * result;
			}
		}
	}
	cout << f_cnt << " " << a_cnt << '\n';
	return 0;
}