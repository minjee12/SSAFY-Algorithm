// 파이프 옮기기 1
// https://www.acmicpc.net/problem/17070

#include <iostream>
#include <queue>
#include <vector>
#define MAX 17

using namespace std;

int N = 0;
int board[MAX][MAX];

// →, ↘, ↓ 방향
int dx[] = { 0, 1, 1 };
int dy[] = { 1, 0, 1 };
int cnt = 0;

void bfs()
{
	//            좌표         방향
	queue<pair<pair<int, int>, int>> q;
	q.push({ {0, 1}, 0 });

	while (q.size()) {
		int cx = q.front().first.first;
		int cy = q.front().first.second;
		int cd = q.front().second;
		q.pop();

		for (int i = 0; i < 2; i++) {
			if (cd < 2 && cd != i) continue;
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= N || ny >= N || board[nx][ny] == 1) continue;
			if (nx == N - 1 && ny == N - 1) {
				cnt++;
				continue;
			}
			q.push({ {nx, ny}, i });
		}
		// 대각선 이동
		bool flag = true;
		for (int i = 0; i < 3; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= N || ny >= N || board[nx][ny] == 1) {
				flag = false;
				break;
			}
		}
		if (flag)
		{
			int nx = cx + dx[2];
			int ny = cy + dy[2];
			if (nx == N - 1 && ny == N - 1) cnt++;
			else q.push({ {nx, ny}, 2 });
		}
	}
	return;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
		}
	}
	bfs();
	cout << cnt << "\n";
	return 0;
}