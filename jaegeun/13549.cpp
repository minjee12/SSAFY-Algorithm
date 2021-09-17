// 숨바꼭질 3
// https://www.acmicpc.net/problem/13549

#include <iostream>
#include <queue>
#include <cstring>
#define MAX 100001

using namespace std;

int N = 0, K = 0;

int visited[MAX];

int get_next_n(int index, int cn)
{
	if (index == 0) return cn * 2;
	if (index == 1) return cn + 1;
	if (index == 2) return cn - 1;
}

int get_weight(int index)
{
	if (index == 0) return 0;
	else return 1;
}

int dijkstra()
{
	queue<int> q;
	q.push(N);
	visited[N] = 0;

	while (q.size())
	{
		int cn = q.front();
		q.pop();

		for (int i = 0; i < 3; i++)
		{
			int nn = get_next_n(i, cn);
			if (nn < 0 || nn >= MAX) continue;
			if (visited[nn] == -1)
			{
				visited[nn] = visited[cn] + get_weight(i);
				q.push(nn);
			}
			else
			{
				int new_weight = visited[cn] + get_weight(i);
				if (visited[nn] > new_weight)
				{
					visited[nn] = new_weight;
					q.push(nn);
				}
			}
		}
	}
	return visited[K];
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> K;
	memset(visited, -1, sizeof(visited));
	cout << dijkstra() << "\n";
	return 0;
}