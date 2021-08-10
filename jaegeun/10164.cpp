// 격자상의 경로
// https://www.acmicpc.net/problem/10164

#include <iostream>

#define SIZE 15 + 1

using namespace std;

int N = 0, M = 0, K = 0;
int board[SIZE][SIZE] = { 0, };


int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M >> K;

	int circle_x = 0;
	int circle_y = 0;

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cnt++;
			if (cnt == K) // 동그라미 위치 계산
			{
				circle_x = i;
				circle_y = j;
			}
		}
	}

	// 동그라미 위치까지 0행, 0열 채우기
	for (int i = 0; i <= circle_x; i++)
		board[i][0] = 1;
	for (int i = 0; i <= circle_y; i++)
		board[0][i] = 1;

	// 동그라미 위치까지 경로 개수 세기
	for (int i = 1; i <= circle_x; i++) {
		for (int j = 1; j <= circle_y; j++) {
			board[i][j] = board[i - 1][j] + board[i][j - 1];
		}		
	}

	// 동그라미 위치 열, 행을 현재 값으로 채우기
	for (int i = circle_x; i < N; i++)
		board[i][circle_y] = board[circle_x][circle_y];
	for (int i = circle_y; i < M; i++)
		board[circle_x][i] = board[circle_x][circle_y];

	// 동그라미 위치부터 끝 점까지 개수 세기
	for (int i = circle_x + 1; i < N; i++) {
		for (int j = circle_y + 1; j < M; j++) {
			board[i][j] = board[i - 1][j] + board[i][j - 1];
		}
	}

	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < M; j++) {
	//		cout << board[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	cout << board[N - 1][M - 1];
	return 0;
}