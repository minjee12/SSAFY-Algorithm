// 마법사 상어와 복제
// https://www.acmicpc.net/problem/23290

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

#define MAX 20001
using namespace std;

int M, S;

// 상어 위치
int shark_x, shark_y;

int fish_dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int fish_dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

int shark_dx[] = { -1, 0, 1, 0 };
int shark_dy[] = { 0, -1, 0, 1 };

vector<int> board[5][5];
queue<int> _smell[5][5];
vector<int> _copy[5][5];
vector<int> _move[5][5];

void print_board(int opt) {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			cout << "(" << i << ", " << j << ") : ";
			if (opt == 0) {
				for (auto x : board[i][j]) {
					cout << x + 1 << " ";
				}
			}
			else if (opt == 1) {
				for (auto x : _copy[i][j]) {
					cout << x + 1 << " ";
				}
			}
			cout << "\n";
		}
	}
	cout << "\n";
}

// 복사
void copy_fish(int dist) {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (dist == 0) { // 복제 마법
				_copy[i][j].resize((int)(board[i][j].size())); // 목적지 크기 지정
				copy(board[i][j].begin(), board[i][j].end(), _copy[i][j].begin()); // 복사
			}
			else if (dist == 1) { // 물고기 이동
				board[i][j].clear();
				board[i][j].resize((int)(_move[i][j].size())); // 목적지 크기 지정
				copy(_move[i][j].begin(), _move[i][j].end(), board[i][j].begin()); // 복사
			}
			else if (dist == 2) {
				for (auto x : _copy[i][j]) {
					board[i][j].push_back(x);
				}
			}
		}
	}
}

void move_next_direction(int x, int y, int d) {
	for (int i = 0; i < 8; i++) {
		int nd = (d + 8 - i) % 8;
		int nx = x + fish_dx[nd];
		int ny = y + fish_dy[nd];
		if (nx < 1 || nx > 4 || ny < 1 || ny > 4) continue;
		if (nx == shark_x && ny == shark_y) continue;
		if (_smell[nx][ny].size()) continue;
		_move[nx][ny].push_back(nd);
		return;
	}
	_move[x][y].push_back(d);
}

// 2, 물고기 이동
void move_fish() {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (auto x : board[i][j]) {
				move_next_direction(i, j, x);
			}
		}
	}
}

pair<int, int> final_path[3];
int max_fish = 0;
pair<int, int> record[3];
bool is_first = true;
bool visited[5][5];

void find_path(int level, int x, int y, int total_fish) {
	if (level == 3) {
		if (is_first) {
			memcpy(final_path, record, sizeof(final_path));
			max_fish = total_fish;
			is_first = false;
		}
		else if (max_fish < total_fish && !is_first) {
			max_fish = total_fish;
			memcpy(final_path, record, sizeof(final_path));
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nx = x + shark_dx[i];
		int ny = y + shark_dy[i];
		if (nx < 1 || nx > 4 || ny < 1 || ny > 4) continue; // 불가능 이동법
		record[level] = { nx, ny };
		if (!visited[nx][ny]) {
			visited[nx][ny] = true;
			find_path(level + 1, nx, ny, total_fish + board[nx][ny].size());
			visited[nx][ny] = false;
		}
		else {
			find_path(level + 1, nx, ny, total_fish);
		}
		record[level] = { 0, 0 };
	}
}

void eat_fish(int s) {
	for (int i = 0; i < 3; i++) {
		int cx = final_path[i].first;
		int cy = final_path[i].second;
		if (board[cx][cy].size()) {
			_smell[cx][cy].push(s);
		}
		board[cx][cy].clear();
	}
	shark_x = final_path[2].first;
	shark_y = final_path[2].second;
}

void pop_smell(int s) {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (_smell[i][j].size() && _smell[i][j].front() == s - 2) _smell[i][j].pop();
		}
	}
}

void solve() {
	for (int s = 0; s < S; s++) {
		for (int i = 0; i < 3; i++) {
			final_path[i] = { 0, 0 };
			record[i] = { 0, 0 };
		}
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				_copy[i][j].clear();
				_move[i][j].clear();
			}
		}
		is_first = true;
		max_fish = 0;
		memset(visited, 0, sizeof(visited));

		// 1. 복제
		copy_fish(0);
		// 2. 물고기 이동
		move_fish();
		copy_fish(1);
		// 3. 상어 이동
		find_path(0, shark_x, shark_y, 0);
		eat_fish(s);
		// 4. 냄새 사라짐
		pop_smell(s);
		// 5. 복제 마법 실행
		copy_fish(2);
	}
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> M >> S;

	for (int i = 0; i < M; i++) {
		int fx, fy, d; cin >> fx >> fy >> d;
		d--;
		board[fx][fy].push_back(d);
	}
	cin >> shark_x >> shark_y;

	solve();
	int result = 0;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			result += board[i][j].size();
		}
	}

	cout << result;

	return 0;
}