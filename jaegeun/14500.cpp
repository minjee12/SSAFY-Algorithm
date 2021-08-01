#include <iostream>


using namespace std;

int si = 0;
int sj = 0;


int n, m = 0;
int result = 0;

//            »ó ÇÏ ÁÂ  ¿ì
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1 ,1 };

int map[500][500] = { 0, };
int visited[500][500] = { 0, };

int max(int a, int b)
{
	return a > b ? a : b;
}

void dfs(int x, int y, int before, int level)
{
	if (level == 3)
	{
		result = max(result, before);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (0 <= nx && nx < n && 0 <= ny && ny < m)
		{
			if (!visited[nx][ny])
			{
				visited[nx][ny] = 1;
				dfs(nx, ny, map[nx][ny] + before, level + 1);
				visited[nx][ny] = 0;
			}
		}
	}
}

void expt_dfs(int x, int y)
{
	int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

	// ¡á¡à¡á
	//   ¡á
	if (x + 1 < n && 0 <= y - 1 && y + 1 < m)
	{
		x1 = map[x][y] + map[x + 1][y] + map[x][y - 1] + map[x][y + 1];
	}
	// ¡á
	// ¡à¡á
	// ¡á
	if (0 <= x - 1 && x + 1 < n && y + 1 < m)
	{
		x2 = map[x][y] + map[x - 1][y] + map[x + 1][y] + map[x][y + 1];
	}
	//	 ¡á
	// ¡á¡à
	//	 ¡á
	if (0 <= x - 1 && x + 1 < n && 0 <= y - 1)
	{
		x3 = map[x][y] + map[x - 1][y] + map[x + 1][y] + map[x][y - 1];
	}
	//   ¡á
	// ¡á¡à¡á
	if (0 <= x - 1 && 0 <= y - 1 && y + 1 < m)
	{
		x4 = map[x][y] + map[x - 1][y] + map[x][y - 1] + map[x][y + 1];
	}
	
	result = max(result, max(max(x1, x2), max(x3, x4)));
	return;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}

	for (si = 0; si < n; si++)
	{
		for (sj = 0; sj < m; sj++)
		{
			visited[si][sj] = 1;
			dfs(si, sj, map[si][sj], 0);
			expt_dfs(si, sj);
			visited[si][sj] = 0;
		}
	}
	cout << result;
	return 0;
}