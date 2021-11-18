#include <iostream>
using namespace std;

int n;
int obs = 3;
char map[7][7];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

int tracking(int y, int x) {
	//상하좌우 방향에 장애물이 있으면 체크
	int visited[4] = { 0, };

	//y, x로부터 1만큼 멀어진 칸 확인 ,,,, T 바로 옆에 S가 있으면 감시 피할 수 없음
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
		if (map[ny][nx] == 'S') return 0;
		if (map[ny][nx] == 'O') visited[i] = 1;
	}

	//y, x로부터 2, 3, 4 만큼 멀어진 칸 확인
	for (int j = 2; j <= 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (visited[i] == 1) continue;
			int ny = y + j * dy[i];
			int nx = x + j * dx[i];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (map[ny][nx] == 'O') visited[i] = 1;
			if (map[ny][nx] == 'S' && obs == 0) return 0;
			if (map[ny][nx] == 'S' && obs > 0) {
				ny = y + (j-1) * dy[i];
				nx = x + (j-1) * dx[i];
				map[ny][nx] = 'O';
				visited[i] = 1;
				obs--;
			}
		}
	}

	return 1;
}

int main() {
	//input
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 'T') {
				int check = tracking(i, j);
				if (check == 0) {
					cout << "NO" << "\n";
					exit(0);
				}
			}
		}
	}

	cout << "YES" << "\n";

	return 0;
}