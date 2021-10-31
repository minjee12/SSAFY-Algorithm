#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

#define MAX 20
using namespace std;
//			   동, 서, 북,남
int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };

int R, C, K; // 집 크기, 온도

int home[MAX][MAX];
int temp[MAX][MAX]; // 온도값 저장
int temp_temp[MAX][MAX]; // 임시 온도값
bool wall[MAX][MAX][5]; // 벽 저장
bool visited[MAX][MAX]; // 방문 확인
vector<pair<pair<int, int>, int>> heater_pos; // 온풍기 x, y, 바람 방향
vector<pair<int, int>> check_pos;

bool check_temp() {
	for (auto x : check_pos) {
		if (temp[x.first][x.second] < K) return false;
	}
	return true;
}

void print_temp() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (temp[i][j]) cout << temp[i][j];
			else cout << 0;
			cout << " ";
		}
		cout << "\n";
	}
}

// 온풍기 가동
void heater_spread(int heater_x, int heater_y, int direct) {
	memset(temp_temp, 0, sizeof(temp_temp));
	memset(visited, 0, sizeof(visited));
	int st_x = heater_x + dx[direct];
	int st_y = heater_y + dy[direct];
	temp_temp[st_x][st_y] = 5;
	visited[st_x][st_y] = true;
	queue < pair<int, int>>q;
	q.push({ st_x, st_y });
	while (q.size()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		if (temp_temp[cx][cy] == 1) continue;
		if (direct == 1) {
			for (int i = -1; i <= 1; i++) {
				int nx = cx + i;
				int ny = cy + dy[direct];
				if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
				if (temp_temp[nx][ny]) continue;
				if (visited[nx][ny]) continue;
				if (i == -1) {
					if (wall[cx][cy][3]) continue;
					if (wall[nx][ny][2]) continue;
				}
				if (i == 0) {
					if (wall[cx][cy][direct]) continue;
				}
				if (i == 1) {
					if (wall[cx][cy][4]) continue;
					if (wall[nx][ny][2]) continue;
				}
				q.push({ nx, ny });
				visited[nx][ny] = true;
				temp_temp[nx][ny] = temp_temp[cx][cy] - 1;
			}
		}
		else if (direct == 2) {
			for (int i = -1; i <= 1; i++) {
				int nx = cx + i;
				int ny = cy + dy[direct];
				if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
				if (temp_temp[nx][ny]) continue;
				if (visited[nx][ny]) continue;
				if (i == -1) {
					if (wall[cx][cy][3]) continue;
					if (wall[nx][ny][1]) continue;
				}
				if (i == 0) {
					if (wall[cx][cy][direct]) continue;
				}
				if (i == 1){
					if(wall[cx][cy][4]) continue;
					if (wall[nx][ny][1]) continue;
				}
				q.push({ nx, ny });
				visited[nx][ny] = true;
				temp_temp[nx][ny] = temp_temp[cx][cy] - 1;
			}
		}
		else if (direct == 3) {
			for (int i = -1; i <= 1; i++) {
				int nx = cx + dx[direct];
				int ny = cy + i;
				if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
				if (temp_temp[nx][ny]) continue;
				if (visited[nx][ny]) continue;
				if (i == -1) {
					if (wall[cx][cy][2]) continue;
					if (wall[nx][ny][4]) continue;
				}
				if (i == 0) {
					if (wall[cx][cy][direct]) continue;
				}
				if (i == 1) {
					if (wall[cx][cy][1]) continue;
					if (wall[nx][ny][4]) continue;
				}
				q.push({ nx, ny });
				visited[nx][ny] = true;
				temp_temp[nx][ny] = temp_temp[cx][cy] - 1;
			}
		}
		else if(direct == 4) {
			for (int i = -1; i <= 1; i++) {
				int nx = cx + dx[direct];
				int ny = cy + i;
				if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
				if (temp_temp[nx][ny]) continue;
				if (visited[nx][ny]) continue;
				if (i == -1) {
					if (wall[cx][cy][2]) continue;
					if (wall[nx][ny][3]) continue;
				}
				if (i == 0) {
					if (wall[cx][cy][direct]) continue;
				}
				if (i == 1) {
					if (wall[cx][cy][1]) continue;
					if (wall[nx][ny][3]) continue;
				}
				q.push({ nx, ny });
				visited[nx][ny] = true;
				temp_temp[nx][ny] = temp_temp[cx][cy] - 1;
			}
		}
		
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			temp[i][j] += temp_temp[i][j];
		}
	}
}

void heat_home() {
	for (int i = 0; i < heater_pos.size(); i++) {
		int h_x = heater_pos[i].first.first;
		int h_y = heater_pos[i].first.second;
		int h_d = heater_pos[i].second;

		heater_spread(h_x, h_y, h_d);
	}
}

void spread_temp() {
	int temp_temp[MAX][MAX] = { 0, };
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (temp[i][j] > 0) {
				int base_temp = temp[i][j];
				for (int d = 1; d <= 4; d++) {
					bool flag = false;
					// 벽 확인
					if (wall[i][j][d]) continue;
					int nx = i + dx[d];
					int ny = j + dy[d];
					if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
					if (temp[i][j] <= temp[nx][ny]) continue;
					int diff = (temp[i][j] - temp[nx][ny]) / 4;
//					int split_temp = diff / 4;
					temp_temp[nx][ny] += diff;
					base_temp -= diff;
				}
				temp_temp[i][j] += base_temp;
			}
		}
	}
	memcpy(temp, temp_temp, sizeof(temp));
}

void decrease_temp() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (i == 0 && temp[i][j] > 0) {
				temp[i][j]--;
				continue;
			}
			if (i == R - 1 && temp[i][j] > 0) {
				temp[i][j]--;
				continue;
			}
			if (j == 0 && temp[i][j] > 0) {
				temp[i][j]--;
				continue;
			}
			if (j == C - 1 && temp[i][j] > 0) {
				temp[i][j]--;
				continue;
			}
		}
	}
}

int main(){
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> R >> C >> K;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> home[i][j];
			if ( 0< home[i][j] && home[i][j] < 5) {
				heater_pos.push_back({ {i, j}, home[i][j] });
			}
			if (home[i][j] == 5) {
				check_pos.push_back({ i, j });
			}
		}
	}
	int W; cin >> W;
	for (int i = 0; i < W; i++) {
		int x, y, t; cin >> x >> y >> t;
		x--;
		y--;
		if (t == 0) { // (x, y)와 (x-1, y) 사이 벽
			wall[x][y][3] = true; // 북
			wall[x - 1][y][4] = true; // 남
		}
		else { // (x, y)와 (x, y-1) 사이 벽
			wall[x][y][1] = true;
			wall[x][y + 1][2] = true;
		}
	}
	int c_cnt = 0;
	while (true) {
		heat_home();
		spread_temp();
		decrease_temp();
		c_cnt++;
		if (check_temp() || c_cnt > 100) break;
	}
	cout << c_cnt;
	return 0;
}
