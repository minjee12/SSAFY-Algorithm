#include <iostream>
#include <queue>

using namespace std;

int map[101] = { 0, };
int bfs_map[101] = { 0, };
int n, m = 0;

int bfs(int st_pos)
{
	queue<int> q;
	q.push(st_pos);
	bfs_map[st_pos] = 1;
	while (1)
	{
		int cr_pos = q.front();
		q.pop();

		for (int i = 1; i <= 6; i++)
		{
			int nx_pos = cr_pos + i; // 다음 위치
			if (nx_pos == 100)
			{
				return bfs_map[cr_pos] + 1;
			}
			if (nx_pos > 100) continue;

			if (map[nx_pos]) // 사다리 or 뱀이 있는 경우를 먼저 확인
			{
				nx_pos = map[nx_pos];
			}
			if (!bfs_map[nx_pos]) // 방문 안한 경우
			{
				bfs_map[nx_pos] = bfs_map[cr_pos] + 1;
				q.push(nx_pos);
			}
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> n >> m;

	for (int i = 0; i < n + m; i++)
	{
		int from = 0;
		int to = 0;

		cin >> from >> to;

		map[from] = to;
	}

	cout << bfs(1) - 1;
	return 0;
}