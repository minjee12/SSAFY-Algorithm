// 마법사 상어와 비바라기
// https://www.acmicpc.net/problem/21610

#include <iostream>
#include <queue>
#include <cstring>
#define MAX 51
using namespace std;

int N, M;
int backet[MAX][MAX]; // 1 ~ N
bool clouds[MAX][MAX];
bool temp_clouds[MAX][MAX];

//			←, ↖,  ↑, ↗,  →, ↘, ↓ ,↙
int dx[] = {  0, -1, -1, -1,  0,  1,  1,  1};
int dy[] = { -1, -1,  0,  1,  1,  1,  0, -1};

void move_clouds(int d, int step)
{
	memset(temp_clouds, 0, sizeof(temp_clouds));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (clouds[i][j]) { // 구름이 있으면
				int nx = (i + N + ((dx[d] * step) % N)) % N;
				int ny = (j + N + ((dy[d] * step) % N)) % N;
				temp_clouds[nx][ny] = true;
			}
		}
	}
	memcpy(clouds, temp_clouds, sizeof(clouds));
}

void rain_backet()
{
	queue<pair<int, int>> q_copy_water;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (clouds[i][j]) {
				backet[i][j]++; // 비가 내림
				clouds[i][j] = false;
				// 물복사 버그
				q_copy_water.push({ i, j });
			}
		}
	}
	while (q_copy_water.size()) {
		int cx = q_copy_water.front().first;
		int cy = q_copy_water.front().second;
		q_copy_water.pop();

		int cnt = 0;
		for (int i = 0; i < 4; i++) // 1, 3, 5, 7
		{
			int nx = cx + dx[i * 2 + 1];
			int ny = cy + dy[i * 2 + 1];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (!backet[nx][ny]) continue;
			cnt++;
		}
		backet[cx][cy] += cnt;
	}
}

void make_clouds()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (backet[i][j] >= 2 && !temp_clouds[i][j]) {
				clouds[i][j] = true;
				backet[i][j] -= 2;
			}
		}
	}		
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> backet[i][j];
		}
	}
	clouds[N - 1][0] = true;
	clouds[N - 1][1] = true;
	clouds[N-2][0] = true;
	clouds[N-2][1] = true;
	
	int d, step;
	for (int i = 0; i < M; i++)
	{
		cin >> d >> step;
		move_clouds(d - 1, step);
		rain_backet();
		make_clouds();
	}

	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sum += backet[i][j];
		}
	}
	cout << sum << "\n";
	return 0;
}