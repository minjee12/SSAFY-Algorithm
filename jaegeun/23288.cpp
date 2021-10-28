// 주사위 굴리기 2
// https://www.acmicpc.net/problem/23288

#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

#define MAX 21
using namespace std;

int N, M, K;
int board[MAX][MAX];
bool visited[MAX][MAX];

// 			 동 북 서 남
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };
int direct = 0; // 초기 방향 동쪽
int dice_x = 1, dice_y = 1; // 주사위 위치
int dice[] = { 1, 2, 3, 4, 5, 6 };

void print_dice() {
	cout << "\t" << dice[1] << "\n";
	cout << dice[3] << "\t" << dice[0] << "\t" << dice[2] << "\n";
	cout << "\t" << dice[4] << "\n";
	cout << "\t" << dice[5] << "\n";
	cout << "\n";

	cout << "주사위 위치 : (" << dice_x + 1 << ", " << dice_y + 1 << ")\n";
	cout << "\n---------------------------\n";
}

void rotate_dice() {
	if (direct == 0) { // 동쪽으로 구름
		swap(dice[0], dice[3]);
		swap(dice[3], dice[5]);
		swap(dice[5], dice[2]);
		return;
	}
	if (direct == 1) { // 북쪽으로 구름
		swap(dice[0], dice[4]);
		swap(dice[4], dice[5]);
		swap(dice[5], dice[1]);
		return;
	}
	if (direct == 2) { // 서쪽으로 구름
		swap(dice[0], dice[2]);
		swap(dice[2], dice[5]);
		swap(dice[5], dice[3]);
		return;
	}
	if (direct == 3){ // 남쪽으로 구름
		swap(dice[0], dice[1]);
		swap(dice[1], dice[5]);
		swap(dice[5], dice[4]);
		return;
	}
}

int bfs(int x, int y, int num) {
	int cnt = 1;
	memset(visited, 0, sizeof(visited));
	queue<pair<int, int>> q;

	visited[x][y] = true;
	q.push({ x, y });

	while (q.size()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
			if (visited[nx][ny] || board[nx][ny] != num) continue;
			cnt++;
			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}
	return cnt;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> board[i][j];
		}
	}

	int total_score = 0;
	for (int i = 0; i < K; i++) {
		// 다음 칸 확인
		int nx = dice_x + dx[direct];
		int ny = dice_y + dy[direct];

		if (nx < 1 || nx > N || ny < 1 || ny > M) { // 다음칸이 없으면
			direct = (direct + 2) % 4; // 반대 방향으로 변경
		}
		// 굴러감
		rotate_dice(); 
		dice_x = dice_x + dx[direct];
		dice_y = dice_y + dy[direct];

		// 점수 획득
		int step = bfs(dice_x, dice_y, board[dice_x][dice_y]);
		int score = step * board[dice_x][dice_y];
		total_score += score;

		// 주사위 아랫면 A, 칸에 있는 정수 B 비교
		if (dice[5] > board[dice_x][dice_y]) { // A > B
			direct = (direct + 4 - 1) % 4; // 이동방향 시계방향 회전
		}
		else if (dice[5] < board[dice_x][dice_y]) { // A < B
			direct = (direct + 1) % 4; // 이동방향 반시계 방향 회전
		}
	}

	cout << total_score;
	return 0;
}