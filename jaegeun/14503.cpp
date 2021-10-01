// 로봇 청소기
// https://www.acmicpc.net/problem/14503

#include <iostream>
#include <queue>

#define MAX 50

using namespace std;

int N, M;
int board[MAX][MAX];
bool is_cleand[MAX][MAX];

// 0 : 북, 1 : 동, 2 : 남, 3 : 서
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int clean_cnt = 0;

int find_next(int cx, int cy, int cd)
{
	for (int i = 1; i <= 4; i++)
	{
		int nd = (cd + 4 - i) % 4;
		int nx = cx + dx[nd];
		int ny = cy + dy[nd];
		// a. 청소 안했으면 전진하고 1번 진행
		if (board[nx][ny] != 1 && !is_cleand[nx][ny]) {
			return nd; // 0~3 반환
		}
	}
	// 4방향 모두 청소가 되어있거나 벽일경우 바라보는 방향 유지한채로 후진
	int nx = cx + dx[(cd + 2) % 4];
	int ny = cy + dy[(cd + 2) % 4];
	if (board[nx][ny] != 1) return -1;
	return -2; // 후진 안될 경우
}
void clean(int cx, int cy, int cd)
{
	while (true)
	{
		// 현재 위치 청소
		is_cleand[cx][cy] = true;
		clean_cnt++;
		// 2. 현재 방향 기준 왼쪽 방향으로 차례로 탐색
		while (true) {
			int result = find_next(cx, cy, cd);
			if (result >= 0) { // 청소 안한 구역 발견
				cx = cx + dx[result];
				cy = cy + dy[result];
				cd = result;
				break;
			}
			if (result == -1) { // 후진
				cx = cx + dx[(cd + 2) % 4];
				cy = cy + dy[(cd + 2) % 4];
			}
			if (result == -2) return;
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;
	int rx, ry, rd; cin >> rx >> ry >> rd;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> board[i][j];
		}
	}

	clean(rx, ry, rd);
	cout << clean_cnt << "\n";
	return 0;
}