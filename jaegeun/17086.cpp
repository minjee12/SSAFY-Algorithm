// 아기상어 (2)

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int map[51][51] = { 0, };

int visited[51][51] = { 0, };

int n = 0, m = 0;

int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int bfs(int x, int y)
{
	visited[x][y] = 1;
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	while (q.size())
	{
		pair<int, int> p = q.front();
		int cx = p.first;
		int cy = p.second;
		
		q.pop();

		for (int i = 0; i < 8; i++)
		{
			int nx = dx[i] + cx; // 다음 인덱스 계산
			int ny = dy[i] + cy;

			if (map[nx][ny] == 1)// 다른 아기 상어와 만난 경우
			{
				return visited[cx][cy];
			}
			if (0 <= nx && nx < n && 0 <= ny && ny < m) // 배열 인덱스 확인
			{
				if (!visited[nx][ny]) // 방문하지 않은 경우
				{
					visited[nx][ny] = visited[cx][cy] + 1;
					q.push(make_pair(nx, ny));
				}
			}
		}
	}
	return 0;
}


int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);

	vector<pair<int, int>> p_input;

	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
			if (map[i][j])
				p_input.push_back(make_pair(i, j));
		}
	}

	int max_result = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 0)
			{
				int result = bfs(i, j);
				//cout << i << "," << j << " result : " << result << '\n';
				if (result > max_result)
					max_result = result;
				memset(visited, 0, sizeof(visited));
			}
		}
	}
	cout << max_result;

	return 0;
}