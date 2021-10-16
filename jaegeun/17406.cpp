// 배열 돌리기 4
// https://www.acmicpc.net/problem/17406

#include <iostream>
#include <cstring>

#define MAX 50
using namespace std;

int n, m, k;
int min_sum = 21e8;
int board[MAX][MAX];

int dx[] = { 1, 0, -1, 0};
int dy[] = { 0, 1, 0, -1 };

int opt[6][3] = { 0, };
bool used[6] = { 0, };

// 배열 돌리기
void rotate_board(int r, int c, int s) {
	for (int i = 1; i <= s; i++) { // s번 반복
		int cx = r - i; // swap 시작 위치
		int cy = c - i;
		for (int d = 0; d < 4; d++) { // 방향 남 동 북 서 진행
			for (int cnt = 0; cnt < i * 2; cnt++) { // i * 2 번 만큼 해당 방향 swap 진행
				int nx = cx + dx[d];
				int ny = cy + dy[d];
				if (nx == r - i && ny == c - i) break; // 다음 칸이 시작 위치일 경우 종료
				swap(board[nx][ny], board[cx][cy]);
				cx = nx; // 현재 위치 갱신
				cy = ny;
			}
		}
	}
}

// 각 행의 합 중 최솟값 반환
int get_min_board_row() { 
	int min_row = 21e8;
	for (int i = 0; i < n; i++) {
		int row_sum = 0;
		for (int j = 0; j < m; j++) {
			row_sum += board[i][j];
		}
		min_row = min(min_row, row_sum);
	}
	return min_row;
}

// 완전 탐색. 연산 진행 경우의 수 모두 탐색
void run(int level) {
	if (level == k) {
		min_sum = min(min_sum, get_min_board_row());
		return;
	}
	int temp_board[MAX][MAX] = { 0, }; 
	memcpy(temp_board, board, sizeof(board)); // 현재 board 상황 복사
	for (int i = 0; i < k; i++) {
		if (!used[i]) {
			used[i] = true;
			rotate_board(opt[i][0] - 1, opt[i][1] - 1, opt[i][2]); // 배열 돌리기 진행
			run(level + 1);
			memcpy(board, temp_board, sizeof(board)); // board 상황 원상 복구하기
			used[i] = false;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		cin >> opt[i][0] >> opt[i][1] >> opt[i][2];
	}
	run(0);

	cout << min_sum;
	return 0;
}