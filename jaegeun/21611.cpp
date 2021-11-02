// 마법사 상어와 블리자드
// https://www.acmicpc.net/problem/21611

#include <iostream>
#include <vector>
#include <cstring>

#define MAX 50
using namespace std;

int N, K;

//			 서 남 동 북
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

int bilzzard_dx[] = {0, -1, 1, 0, 0 };
int bilzzard_dy[] = {0, 0, 0, -1, 1 };

int board[MAX][MAX];
int sequence[MAX][MAX];

int marble[MAX * MAX + 1];
int temp_marble[MAX * MAX + 1]; // 임시 구슬
int group_cnt[MAX * MAX][2]; // 그룹 개수 세기 연속 개수, 숫자
int marble_cnt = 0;
int score = 0; // 점수

void fill_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = marble[sequence[i][j]];
		}
	}
}

void print_board() {
	fill_board();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void print_sequence() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << sequence[i][j] << " ";
		}
		cout << "\n";
	}
}

void fill_sequence() {
	int cx = N / 2;
	int cy = N / 2;

	int cnt = 0;
	int d_cnt = 1;
	int d = 0;
	sequence[0][0] = N * N - 1;
	while (true) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < d_cnt; j++) {
				sequence[cx][cy] = cnt++;
				cx = cx + dx[d];
				cy = cy + dy[d];
				if (cx == 0 && cy == 0) return;
			}
			d = (d + 1) % 4;
		}
		d_cnt++;
	}
}

void init_marble() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j]) {
				marble[sequence[i][j]] = board[i][j];
				marble_cnt++;
			}
		}
	}
}

void destory_marble(int r, int d) {
	int cx = N / 2 + bilzzard_dx[d];
	int cy = N / 2 + bilzzard_dy[d];

	for (int s = 0; s < r; s++) {
		marble[sequence[cx][cy]] = 0;
		cx = cx + bilzzard_dx[d];
		cy = cy + bilzzard_dy[d];
	}
}

// 구슬 당기기
void pull_marble() {
	memset(temp_marble, 0, sizeof(temp_marble));
	int marble_before = marble_cnt;
	int index = 1;
	
	for (int i = 1; i <= marble_before; i++) {
		if (marble[i]) {
			temp_marble[index++] = marble[i];
		}
		else marble_cnt--;
	}
	memcpy(marble, temp_marble, sizeof(marble));
}

// 구슬 터짐
void bomb_marble() {
	while (true) {
		int cur_idx = 2;
		int marble_num = marble[1]; // 현재 구슬 번호
		int marble_s_cnt = 1; // 연속 횟수
		int before = marble_cnt;
		while (true) {
			if (marble[cur_idx] == 0) break;

			if (marble[cur_idx] == marble_num) marble_s_cnt++;
			else {
				marble_num = marble[cur_idx];
				marble_s_cnt = 1;
			}
			if (marble_s_cnt >= 4 && marble[cur_idx + 1] != marble_num) {
				for (int i = 0; i < marble_s_cnt; i++) {
					marble[cur_idx - i] = 0; // 구슬 폭발
				}
				//printf("score = %d, mable_s_cnt : %d, marble_num : %d \n", score, marble_s_cnt, marble_num);
				score += marble_s_cnt * marble_num;
				// 초기화
				marble_num = 0;
			}
			cur_idx++;
		}
		pull_marble();
		if (before == marble_cnt) break;
	}
}

void fill_marble() {
	memset(temp_marble, 0, sizeof(temp_marble));
	memset(group_cnt, 0, sizeof(group_cnt));
	int index = 1;
	
	int m_num = marble[1];
	int m_cnt = 1;
	for (int i = 2; i <= marble_cnt + 1; i++) { // 구슬 개수 + 1만큼 반복
		if (m_num == marble[i]) m_cnt++;
		else {
			group_cnt[index][0] = m_cnt;
			group_cnt[index++][1] = m_num;
			m_num = marble[i];
			m_cnt = 1;
		}
	}
	index = 1;
	for (int i = 1; i <= marble_cnt; i++) {
		if (index > N * N - 1) break;
		temp_marble[index++] = group_cnt[i][0];
		temp_marble[index++] = group_cnt[i][1];
	}
	memcpy(marble, temp_marble, sizeof(marble));
	for (int i = 1; i <= N * N; i++) {
		if (marble[i] == 0) {
			marble_cnt = i - 1;
			break;
		}
	}
#if _DEBUG
	cout << "marble_cnt : " << marble_cnt << "\n";
#endif // _DEBUG

}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	
	cin >> N >> K;
	fill_sequence();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		} 
	}
	init_marble();
	for (int i = 0; i < K; i++) {
		int range, d; cin >> d >> range;
		destory_marble(range, d);
#if _DEBUG
		print_board();
#endif
		pull_marble();
#if _DEBUG
		print_board();
#endif
		bomb_marble();
#if _DEBUG
		print_board();
#endif
		fill_marble();
#if _DEBUG
		print_board();
		cout << "----------------------------\n";
#endif
	}
	cout << score;
	return 0;
}