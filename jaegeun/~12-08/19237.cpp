// 어른 상어
// https://www.acmicpc.net/problem/19237

#define MAX 20

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;


// 1: 상, 2: 하, 3: 좌, 4: 우
int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, -1, 1 };

typedef struct {
	int direct[5][4];
}d_prior;

typedef struct {
	int x, y; // 현재 위치
	int d; // 현재 방향
	int num; // 상어 번호
	d_prior shark_prioir; // 상어 이동 우선순위
	bool enable; // 쫒겨났는지 
}shark;

int N, M, K;

int time_cnt = 0;
// 냄새 남긴 시간, 냄새를 남긴 상어 번호
pair<int,int> small[MAX][MAX];

// 상어 현재 위치
vector<shark> shark_vect;
int shark_cnt; // 남은 상어 수

bool compair(shark a, shark b) {
	return a.num < b.num;
}

// 냄새 뿌리기
void marking() {
	for (int i = 0; i < shark_vect.size(); i++) {
		if (shark_vect[i].enable) {
			int cx = shark_vect[i].x;
			int cy = shark_vect[i].y;
			small[cx][cy] = { K, shark_vect[i].num };
		}
	}
}

// 상하좌우 빈 칸 개수 탐색
int get_empty_cell(int x, int y) {
	int cnt = 0;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (small[nx][ny].first == 0) cnt++;
	}
	return cnt;
}

// 빈 칸으로 이동
bool move_empty_cell(int shark_idx) {
	int cx = shark_vect[shark_idx].x;
	int cy = shark_vect[shark_idx].y;
	int cd = shark_vect[shark_idx].d;
	bool is_empty = false;

	for (int d = 0; d < 4; d++) {
		// 현재 자기 방향의 우선순위 대로 탐색
		int nx = cx + dx[shark_vect[shark_idx].shark_prioir.direct[cd][d]];
		int ny = cy + dy[shark_vect[shark_idx].shark_prioir.direct[cd][d]];
		if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
		// 빈 칸 탐색
		if (small[nx][ny].first == 0) {
			is_empty = true;
			shark_vect[shark_idx].x = nx;
			shark_vect[shark_idx].y = ny;
			shark_vect[shark_idx].d = shark_vect[shark_idx].shark_prioir.direct[cd][d];
			//cout << shark_vect[shark_idx].num << "번 상어 (" << cx + 1 << "," << cy + 1 << ") -> (" << nx + 1 << "," << ny + 1 << ")로 빈칸 이동\n";
			return true;
		}
	}
	return false;
}

// 자기 냄새로 이동
void move_self_cell(int shark_idx) {
	int cx = shark_vect[shark_idx].x;
	int cy = shark_vect[shark_idx].y;
	int cd = shark_vect[shark_idx].d;

	for (int d = 0; d < 4; d++) {
		int nx = cx + dx[shark_vect[shark_idx].shark_prioir.direct[cd][d]];
		int ny = cy + dy[shark_vect[shark_idx].shark_prioir.direct[cd][d]];
		if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
		// 자기 자신의 냄새
		if (small[nx][ny].second == shark_vect[shark_idx].num) {
			shark_vect[shark_idx].x = nx;
			shark_vect[shark_idx].y = ny;
			shark_vect[shark_idx].d = shark_vect[shark_idx].shark_prioir.direct[cd][d];
			//cout << shark_vect[shark_idx].num << "번 상어 (" << cx  + 1 << "," << cy + 1 << ") -> (" << nx + 1 << "," << ny + 1 << ")로 자기 냄새로 이동\n";
			return;
		}
	}
}

// 상어 이동
void move_shark() {
	vector<int> board[MAX][MAX];
	// 동시에 이동
	for (int i = 0; i < shark_vect.size(); i++) {
		// 격자 내부에 있는 경우
		if (shark_vect[i].enable) {
			if (move_empty_cell(i)) {
				board[shark_vect[i].x][shark_vect[i].y].push_back(shark_vect[i].num);
				continue;
			}
			else {
				move_self_cell(i);
				board[shark_vect[i].x][shark_vect[i].y].push_back(shark_vect[i].num);
			}
		}
	}

	for (int i = 0; i < shark_vect.size(); i++) {
		if (shark_vect[i].enable) {
			int cx = shark_vect[i].x;
			int cy = shark_vect[i].y;
			int cnum = shark_vect[i].num;
			if (board[cx][cy].size() >= 2) {
				for (int s = 0; s < board[cx][cy].size(); s++) {					
					int stack_num = board[cx][cy][s];
					if (cnum < stack_num) {
						//cout << "(" << cx + 1 << "," << cy + 1 << ") 중복. " << stack_num << "쫒겨남\n";
						shark_vect[stack_num - 1].enable = false;
						shark_cnt--;
					}
				}
			}
		}
	}
}

// 냄새 사라짐 - K번 이동 후 사라짐
void rm_small() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// 냄새가 있는 경우
			if (small[i][j].second != 0) {
				if (small[i][j].first >= 1) small[i][j].first--;
				if (small[i][j].first == 0) {
					small[i][j] = { 0, 0 };
				}
			}
		}
	}
}

void solve() {
	shark_cnt = shark_vect.size();
	marking();
	while (true) {
		if (shark_cnt == 1) break;
		if (time_cnt > 1000) break;
		time_cnt++;
		move_shark(); 
		rm_small();
		marking();
	}
	if (time_cnt > 1000) cout << -1;
	else cout << time_cnt;
	return;
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int num; cin >> num;
			if (num > 0) {
				// x, y, 방향, 방향 우선순위
				shark_vect.push_back({ i, j, 0, num, {0,}, true });
				//board[i][j].push_back(num);
			}
		}
	}
	sort(shark_vect.begin(), shark_vect.end(), compair);
	for (int i = 0; i < M; i++) {
		cin >> shark_vect[i].d; // 현재 방향
	}
	for (int i = 0; i < M; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int d = 0; d < 4; d++) {
				cin >> shark_vect[i].shark_prioir.direct[j][d];
			}
		}
	}
	solve();
	return 0;
}