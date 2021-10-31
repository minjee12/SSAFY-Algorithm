#include <iostream>
#include <vector>

#define MAX 20
using namespace std;
//			   동, 서, 북,남
int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };

int R, C, K; // 집 크기, 온도

int home[MAX][MAX];
int temp[MAX][MAX]; // 온도값 저장
vector<int> wall[MAX][MAX]; // 벽 저장
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
			else cout << " ";
			cout << " ";
		}
		cout << "\n";
	}
}

// 온풍기 가동
void heater_spread(int heater_x, int heater_y, int direct) {
	int temp_heat = 5;
	int st_x = heater_x + dx[direct];
	int st_y = heater_y + dy[direct];
	for (int i = 0; i < 5; i++) {
		if (direct <= 2) {
			for (int j = 0; j < i * 2 + 1; j++) {
				if (st_x + j < 0) continue;
				if (st_x + j >= R) break;
				bool wall_flag = false; // 벽이 있을 경우
				// 벽 확인
				for (int w = 0; w < wall[st_x + j][st_y].size(); w++) {
					if (direct == 1 && wall[st_x + j][st_y][w] == 2) wall_flag = true;
					if (direct == 2 && wall[st_x + j][st_y][w] == 1) wall_flag = true;
				}
				if (wall_flag) continue; // 방향과 상반되는 벽 있을 경우 채우지 않음
				temp[st_x + j][st_y] += 5 - i;
			}
			st_x--;
			st_y = st_y + dy[direct];
			if (st_y >= C) break;
		}
		else {
			for (int j = 0; j < i * 2 + 1; j++) {
				if (st_y + j < 0) continue;
				if (st_y + j >= C) break;
				bool wall_flag = false;
				// 벽 확인
				for (int w = 0; w < wall[st_x][st_y + j].size(); w++) {
					if (direct == 3 && wall[st_x][st_y + j][w] == 4) wall_flag = true;
					if (direct == 4 && wall[st_x][st_y + j][w] == 3) wall_flag = true;
				}
				if (wall_flag) continue; // 방향과 상반되는 벽 있을 경우 채우지 않음
				temp[st_x][st_y + j] += 5 - i;
			}
			st_x = st_x + dx[direct];
			if (st_x >= R) break;
			st_y--;
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
					for (int w = 0; w < wall[i][j].size(); w++) {
						if (wall[i][j][w] == d) {
							flag = true;
							break;
						}
					}
					if (flag) continue;
					int nx = i + dx[d];
					int ny = j + dy[d];
					if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
					if (temp[i][j] <= temp[nx][ny]) continue;
					int diff = temp[i][j] - temp[nx][ny];
					int split_temp = diff / 4;
					temp_temp[nx][ny] += split_temp;
					base_temp -= split_temp;
				}
				temp_temp[i][j] += base_temp;
			}
		}
	}
	memcpy(temp, temp_temp, sizeof(temp));

}

void decrease_temp() {
	for (int i = 0; i < C; i++) {
		if (temp[0][i] > 0) temp[0][i]--;
		if (temp[R - 1][i] > 0) temp[R - 1][i]--;
	}
	
	for (int i = 0; i < R; i++) {
		if (temp[i][0] > 0) temp[i][0]--;
		if (temp[i][C - 1] > 0)temp[i][C - 1]--;
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
			wall[x][y].push_back(3); // 북
			wall[x - 1][y].push_back(4); // 남
		}
		else { // (x, y)와 (x, y-1) 사이 벽
			wall[x][y].push_back(1);
			wall[x][y + 1].push_back(2);
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
	cout << "\n\n";
	print_temp();
	cout << c_cnt;
	return 0;
}