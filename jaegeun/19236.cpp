// 청소년 상어
// https://www.acmicpc.net/problem/19236

#include <iostream>
#include <vector>

#define SIZE 4
#define EMPTY 0
#define SHARK -1

using namespace std;

int max_score = 0;
typedef struct {
	bool alive;
	int direction;
	int fx;
	int fy;
}fish_info; // 물고기 정보

fish_info fish_arr[17] = { 0, }; // 물고기 정보
fish_info shark = { 0, }; // 상어 정보
//           ↑  ↖  ←  ↙  ↓  ↘   → ↗
int dx[8] = {-1, -1,  0,  1,  1,  1,  0,  -1};
int dy[8] = { 0, -1, -1, -1,  0,  1,  1,  1};

int board_init[SIZE][SIZE] = { 0, };

void swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

// 보드 출력
void print_board(int b[SIZE][SIZE], bool direction = false)
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (direction) {
				cout << b[i][j] << "," << fish_arr[b[i][j]].direction << "\t";
			}
			else {
				cout << b[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << "=========================" << endl;
}

// 방향 전환
void change_direction(int fish_num)
{
	fish_arr[fish_num].direction = (fish_arr[fish_num].direction + 1) % 8;
}

void move_fish(int board[SIZE][SIZE])
{
	// 숫자가 작은 물고기부터
	for (int i = 0; i < 17; i++)
	{
		if (fish_arr[i].alive) // 살아있는 물고기의 경우
		{
			// 방향 전환 총 8번 반복
			while (true)
			{
				// 물고기 현재 위치
				int cur_fish_x = fish_arr[i].fx;
				int cur_fish_y = fish_arr[i].fy;
				// 현재 방향 기준 다음 위치 계산
				int cur_fish_direction = fish_arr[i].direction;
				int next_fish_x = fish_arr[i].fx + dx[cur_fish_direction];
				int next_fish_y = fish_arr[i].fy + dy[cur_fish_direction];
				if (0 <= next_fish_x && next_fish_x < SIZE && 0 <= next_fish_y && next_fish_y < SIZE) {
					if (board[next_fish_x][next_fish_y] == 0) // 빈칸으로 이동
					{
						// 다음칸으로 위치 변경
						fish_arr[i].fx = next_fish_x;
						fish_arr[i].fy = next_fish_y;
						// board상 위치 변경
						swap(board[cur_fish_x][cur_fish_y], board[next_fish_x][next_fish_y]);
						break; // 다음 물고기 변경
					}
					else if (1 <= board[next_fish_x][next_fish_y] && board[next_fish_x][next_fish_y] <= 16)
						// 물고기와 자리 바꿀 경우
					{
						int swap_fish_num = board[next_fish_x][next_fish_y]; // 자리 바꿀 물고기 번호
						// 자리 바꿀 물고기 위치를 현재 물고기 위치로 변경
						fish_arr[swap_fish_num].fx = cur_fish_x;
						fish_arr[swap_fish_num].fy = cur_fish_y;
						// 현재 물고기 위치를 자리 바꿀 물고기 위치로 변경
						fish_arr[i].fx = next_fish_x;
						fish_arr[i].fy = next_fish_y;
						swap(board[cur_fish_x][cur_fish_y], board[next_fish_x][next_fish_y]);
						break; // 다음 물고기 변경
					}
				}
				change_direction(i); // 현재 물고기의 방향 변경
			}
		}
	}
}

// 상어가 갈 수 있는 위치 중 물고기가 있는 칸 반환
// x, y 상어 위치
vector<pair<int, int>> get_next_shark_positions(int board[SIZE][SIZE], int sx, int sy, int sd)
{
	vector<pair<int, int>> shark_pos;
	int nsx = dx[sd] + sx; // 다음 상어 위치
	int nsy = dy[sd] + sy;
	
	while (true)
	{
		if (0 <= nsx && nsx < SIZE && 0 <= nsy && nsy < SIZE) // board 범위 내에 있을 경우
		{
			if (1 <= board[nsx][nsy] && board[nsx][nsy] <= 16) { // 물고기일 경우 벡터에 추가
				shark_pos.push_back(make_pair(nsx, nsy));
			}
			nsx = dx[sd] + nsx; // 다음 상어 위치
			nsy = dy[sd] + nsy;
		}
		else {
			break;
		}
	}
	return shark_pos;
}

void solve(int board[SIZE][SIZE], int score, int shark_x, int shark_y, int shark_direction)
{
	int board_cpy[SIZE][SIZE] = { 0, };
	memcpy(board_cpy, board, sizeof(board_init));
	fish_info fish_arr_cpy[17] = { 0, }; // 물고기 정보
	// 상어 칸에 해당하는 물고기 먹힘
	move_fish(board_cpy); // 물고기 이동
	memcpy(fish_arr_cpy, fish_arr, sizeof(fish_arr)); // 물고기 이동 상태 저장
	// 상어가 갈 수 있는 위치
	vector<pair<int, int>> shark_positions = get_next_shark_positions(board_cpy, shark_x, shark_y, shark_direction); 
	if (shark_positions.size() == 0) // 먹을 물고기가 없을 경우
	{
		if (score > max_score)
		{
			max_score = score;
			return;
		}
	}

	for (int i = 0; i < shark_positions.size(); i++)
	{
		int shark_next_x = shark_positions[i].first; // 상어의 다음 위치
		int shark_next_y = shark_positions[i].second;
		int next_fish = board_cpy[shark_next_x][shark_next_y]; // 먹힐 물고기
		int shark_next_d = fish_arr[next_fish].direction; // 상어의 다음 방향
		board_cpy[shark_next_x][shark_next_y] = SHARK; // 물고기 먹힘
		board_cpy[shark_x][shark_y] = 0; // 빈칸 처리
		fish_arr[next_fish].alive = false; // 죽음 처리
		solve(board_cpy, score + next_fish, shark_next_x, shark_next_y, shark_next_d);
		fish_arr[next_fish].alive = true; // 살리기
		board_cpy[shark_x][shark_y] = SHARK; // 상어 위치 복구
		board_cpy[shark_next_x][shark_next_y] = next_fish; // 먹힌 물고기 복구
		memcpy(fish_arr, fish_arr_cpy, sizeof(fish_arr)); // 물고기 상태 복구
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int fish_num = 0;
			int fish_direction = 0;
			cin >> fish_num >> fish_direction;
			fish_arr[fish_num] = { true, fish_direction - 1, i, j };
			board_init[i][j] = fish_num;
		}
	}
	int first_fish = board_init[0][0];
	int next_direction = fish_arr[first_fish].direction;
	fish_arr[first_fish].alive = false;
	board_init[0][0] = SHARK;
	solve(board_init, first_fish, 0, 0, next_direction);
	cout << max_score;
	return 0;
}