// 영상처리
// https://www.acmicpc.net/problem/21938

#include <iostream>
#include <queue>
#include <vector>
#define MAX 1000

using namespace std;
int N, M, T;
int cnt = 0;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
int image[3][MAX][MAX];
bool th_image[MAX][MAX];
bool visited[MAX][MAX];

void bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = true;
	while (q.size()) {
		int cx = q.front().first;
		int cy = q.front().second;

		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (visited[nx][ny] || !th_image[nx][ny]) continue;
			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}
}

void count_fig() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (th_image[i][j] && !visited[i][j]) {
				bfs(i, j);
				cnt++;
			}
		}
	}
}
int main( ){
	freopen_s(new FILE*, "text.txt", "r", stdin);
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) {
			int r, g, b; cin >> r >> g >> b;
			image[0][i][j] = r;
			image[1][i][j] = g;
			image[2][i][j] = b;
		}
	}
	cin >> T;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int mean = (image[0][i][j] + image[1][i][j] + image[2][i][j]) / 3;
			if (mean >= T) th_image[i][j] = true;
		}
	}
	count_fig();
	cout << cnt;
	return 0;
}