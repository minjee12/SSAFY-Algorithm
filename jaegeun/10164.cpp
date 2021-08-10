// ���ڻ��� ���
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
			if (cnt == K) // ���׶�� ��ġ ���
			{
				circle_x = i;
				circle_y = j;
			}
		}
	}

	// ���׶�� ��ġ���� 0��, 0�� ä���
	for (int i = 0; i <= circle_x; i++)
		board[i][0] = 1;
	for (int i = 0; i <= circle_y; i++)
		board[0][i] = 1;

	// ���׶�� ��ġ���� ��� ���� ����
	for (int i = 1; i <= circle_x; i++) {
		for (int j = 1; j <= circle_y; j++) {
			board[i][j] = board[i - 1][j] + board[i][j - 1];
		}		
	}

	// ���׶�� ��ġ ��, ���� ���� ������ ä���
	for (int i = circle_x; i < N; i++)
		board[i][circle_y] = board[circle_x][circle_y];
	for (int i = circle_y; i < M; i++)
		board[circle_x][i] = board[circle_x][circle_y];

	// ���׶�� ��ġ���� �� ������ ���� ����
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