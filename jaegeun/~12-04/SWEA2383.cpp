// 점심 식사 시간

#define MAX 10

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;

typedef struct {
	int len;
	int x, y;
}stair_t;

int N;
int room[MAX][MAX];
vector<stair_t> stairs;
vector<pair<int, int>> people;

int min_result;
int sel[MAX];
void print_sel() {
	for (int i = 0; i < N; i++) {
		cout << sel[i] << " ";
	}
	cout << "\n";
}

void calc_time() {
	// 계단까지 이동시간 계산
	int num_people = people.size();
	int move_time[MAX] = { 0, };
	for (int i = 0; i < num_people; i++) {
		int choice_stair = sel[i]; // i번째 사람의 선택 계단
		int st_x = stairs[choice_stair].x;
		int st_y = stairs[choice_stair].y;
		move_time[i] = abs(st_x - people[i].first) + abs(st_y - people[i].second);
	}
	bool in_stair[MAX] = { 0, }; // 계단에 들어간 경우
	int out_cnt = 0; // 계단 이동 완료 숫자

	int m = 0; // 시간
	deque<int> stair1;
 	deque<int> stair2;
	while (out_cnt < num_people) {
		for (int i = 0; i < stair1.size(); i++) {
			stair1[i]--;
		}
		for (int i = 0; i < stair2.size(); i++) {
			stair2[i]--;
		}
		while (true) {
			if (stair1.size() == 0 || stair1.front() != 0) break;
			stair1.pop_front();
			out_cnt++;
		}
		while (true) {
			if (stair2.size() == 0 || stair2.front() != 0) break;
			stair2.pop_front();
			out_cnt++;
		}
		for (int i = 0; i < num_people; i++) {
			// 계단에 들어가지 않았고, 현재 시간이 이동 시간보다 클 때
			if (!in_stair[i] && move_time[i] <= m) {
				if (sel[i] == 0 && stair1.size() < 3) {
					in_stair[i] = true;
					stair1.push_back(stairs[0].len);
				}
				if (sel[i] == 1 && stair2.size() < 3) {
					in_stair[i] = true;
					stair2.push_back(stairs[1].len);
				}
			}
		}
		m++;
	}
	min_result = min(m, min_result);
}

void choice(int level) {
	if (level == people.size()) {
		calc_time();
		return;
	}
	for (int i = 0; i < 2; i++) {
		sel[level] = i;
		choice(level + 1);
	}
}

void solve() {
	memset(sel, 0, sizeof(sel));
	min_result = 1e9;
	choice(0);
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int T; cin >> T;
	for (int t = 0; t < T; t++) {
		memset(room, 0, sizeof(room));
		stairs.clear();
		people.clear();
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> room[i][j];
				if (room[i][j] == 1) {
					people.push_back({ i,j });
				}
				if (room[i][j] >= 2) {
					stairs.push_back({ room[i][j], i, j });
				}
			}
		}
		solve();
		cout << "#" << t + 1 << " " << min_result << "\n";
	}
}