// 미세먼지 안녕!
// https://www.acmicpc.net/problem/17144

#include <iostream>
#include <vector>

#define MAX 50

using namespace std;

pair<int, int> air_cleaner[2]; // 공기 청정기 위치
int c_cnt = 0; // 위치 저장 인덱스

int r, c, t;
		//	북	동	남	서
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int room[MAX][MAX];
vector<int> temp_room[MAX][MAX];

void spread_dust(int x, int y) {
	// 인접한 4 방향으로 확산
	int total_spread = 0;
	int split_amount = room[x][y] / 5;
	if (split_amount > 0) {
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
			if (room[nx][ny] == -1) continue;
			temp_room[nx][ny].push_back(split_amount);
			total_spread += split_amount;
		}
	}
	temp_room[x][y].push_back(room[x][y] - total_spread);
}

void upward_wind() {
	int cx = air_cleaner[0].first;
	int cy = air_cleaner[0].second;
	// 북 동 남 서 방향 swap
	for (int i = 0; i < 4; i++) {
		int roofcnt = 0;
		if (i % 2 == 0) roofcnt = air_cleaner[0].first;
		else roofcnt = c - 1;
		for (int j = 0; j < roofcnt; j++) {
			int nx = dx[i] + cx;
			int ny = dy[i] + cy;
			if (room[cx][cy] == -1) room[nx][ny] = 0;
			else if (room[nx][ny] == -1) break;
			else swap(room[cx][cy], room[nx][ny]);
			cx = nx;
			cy = ny;
		}
	}
}

void downward_wind() {
	int cx = air_cleaner[1].first;
	int cy = air_cleaner[1].second;
	// 남 동 북 서 방향 swap
	for (int i = 0; i < 4; i++) {
		int roofcnt = 0;
		if (i % 2 == 0) roofcnt = r - air_cleaner[1].first - 1;
		else roofcnt = c - 1;
		for (int j = 0; j < roofcnt; j++) {
			int nx = dx[(2 - i + 4) % 4] + cx;
			int ny = dy[(2 - i + 4) % 4] + cy;
			if (room[cx][cy] == -1) room[nx][ny] = 0;
			else if (room[nx][ny] == -1) break;
			else swap(room[cx][cy], room[nx][ny]);
			cx = nx;
			cy = ny;
		}
	}
}

void spread() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (room[i][j] > 0) spread_dust(i, j);
		}
	}
	// 퍼진 먼지 합치기
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (room[i][j] == -1) continue;
			if (temp_room[i][j].size()) {
				int sum = 0;
				for (int s = 0; s < temp_room[i][j].size(); s++) {
					sum += temp_room[i][j][s];
				}
				room[i][j] = sum;
			}
			else room[i][j] = 0;
			temp_room[i][j].clear(); // 탐색 완료 벡터 비우기
		}
	}
}

void clean() {
	upward_wind();
	downward_wind();
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> r >> c >> t;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> room[i][j];
			if (room[i][j] == -1) { // 공기 청정기 위치 저장
				air_cleaner[c_cnt].first = i;
				air_cleaner[c_cnt].second = j;
				c_cnt++;
			}
		}
	}

	for (int i = 0; i < t; i++) {
		spread(); // 먼지 확산
		clean(); // 공기 청정기 가동
	}
	int total_dust = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (room[i][j] == -1) continue;
			total_dust += room[i][j];
		}
	}
	cout << total_dust << "\n";
		
	return 0;
}