// 보물섬
// https://www.acmicpc.net/problem/2589

#include <iostream>
#include <queue>
#include <cstring>
#include <queue>

#define MAX 51
#define LAND 'L'
#define WATER 'W'


using namespace std;

int N = 0, M = 0;

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

char board[MAX][MAX]; // 지도
int visited[MAX][MAX];

int bfs(int x, int y)
{
	memset(visited, 0, sizeof(visited));
	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = 1;

	int cx = 0, cy = 0;
	while (q.size())
	{
		cx = q.front().first;
		cy = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) continue;
			if (board[nx][ny] == WATER) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = visited[cx][cy] + 1;
			q.push({ nx, ny });
		}
	}
	
	return visited[cx][cy] - 1;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;
	vector<pair<int, int>> land_q;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == LAND)
			{
				land_q.push_back({ i, j });
			}
		}
	}
	int max_result = 0;
	for (int i = 0; i < land_q.size(); i++)
	{
		int result = bfs(land_q[i].first, land_q[i].second);
		max_result = result > max_result ? result : max_result;
	}
	cout << max_result << '\n';
	return 0;
}