// 빙산
// https://www.acmicpc.net/problem/2573

#include <iostream>
#include <queue>
#include <cstring>
#define MAX 300 

using namespace std;

int N = 0, M = 0;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int sea[MAX][MAX];
int visited[MAX][MAX];

void bfs(int x, int y)
{
	queue<pair<int, int>> q;
	q.push({ x, y });

	visited[x][y] = 1;

	while (q.size())
	{
		int cx = q.front().first;
		int cy = q.front().second;
		
		q.pop();
		int cnt_zero = 0;
		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) continue;
			// 이전 탐색에서 빙산의 높이가 0이 된 경우, 카운트 하면 안됨
			if (!visited[nx][ny] && !sea[nx][ny]) cnt_zero++;
			if (visited[nx][ny] || !sea[nx][ny]) continue;
			visited[nx][ny] = 1;
			q.push({ nx, ny });
		}
		sea[cx][cy] = sea[cx][cy] - cnt_zero < 0 ? 0 : sea[cx][cy] - cnt_zero;
	}
}

int calc_iceberg_cnt()
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (sea[i][j] && !visited[i][j])
			{
				bfs(i, j);
				cnt++;
			}
		}
	}
	return cnt;
}

int main()
{
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;

	for(int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> sea[i][j];
		}
	}
	int year = 0;
	while (true)
	{
		int cnt = calc_iceberg_cnt();
		if (cnt == 0)
		{
			cout << 0 << '\n';
			return 0;
		}
		if (cnt > 1) break;
		year++;
		memset(visited, 0, sizeof(visited));
	}
	cout << year << '\n';
	return 0;
}