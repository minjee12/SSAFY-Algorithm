// 숨바꼭질 2
// https://www.acmicpc.net/problem/12851

#include <iostream>
#include <queue>

using namespace std;

int N = 0, K = 0;

int cnt = 0;
int min_time = 0;

bool visited[100001];

bool find_bro = false;
int dx[] = { -1, 1 };

void bfs(int x)
{
	queue<pair<int, int>> q;
	visited[x] = true;

	q.push({ x, 0 });

	while (q.size())
	{
		int cx = q.front().first;
		int time = q.front().second;
		q.pop();

		// 같은 깊이의 모든 노드를 탐색하는 BFS의 특성
		// 같은 time일 때 모든 방문 경우의 수 체크
		visited[cx] = true; 

		if (cx == K && find_bro && time == min_time) {
			cnt++;
			continue;
		}

		if (cx == K && !find_bro)
		{
			find_bro = true;
			min_time = time;
			cnt++;
			continue;
		}

		if (cx - 1 >= 0 && !visited[cx - 1]) q.push({ cx - 1, time + 1 });
		if (cx + 1 <= 100000 && !visited[cx + 1]) q.push({ cx + 1, time + 1 });
		if (cx * 2 <= 100000 && !visited[cx * 2]) q.push({ cx * 2, time + 1 });
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> K;
	if (N == K) {
		cout << 0 << '\n' << 1 << '\n';
		return 0;
	}
	bfs(N);
	cout << min_time << '\n' << cnt << '\n';
	return 0;
}