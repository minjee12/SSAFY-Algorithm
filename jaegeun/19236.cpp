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
void print_board(int b[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << b[i][j] << "," << fish_arr[b[i][j]].direction <<"\t";
		}
		cout << endl;
	}
}

// 방향 전환
void change_direction(int fish_num)
{
	fish_arr[fish_num].direction = (fish_arr[fish_num].direction + 1) % 8;
}

// fish_num에 해당하는 물고기와 자리를 바꿀 위치를 nx ny에 저장
bool find_next_fish(int fish_num, int board[SIZE][SIZE], int& nx, int& ny)
{
	int cx = fish_arr[fish_num].fx; // 현재 물고기 x
	int cy = fish_arr[fish_num].fy; // 현재 물고기 y
	for (int i = 0; i < 8; i++)
	{
		int cd = fish_arr[fish_num].direction; // 현재 물고기 방향
		int npx = cx + dx[cd]; // 방향의 위치
		int npy = cy + dy[cd];
		if (0 <= npx && npx < SIZE && 0 <= npy && npy < SIZE) {
			if (board[npx][npy] == 0)
			{
				nx = npx;
				ny = npy;
				return false;
			}
			else if (1 <= board[npx][npy] && board[npx][npy] <= 16) // 다음칸이 물고기일 경우
			{
				if (fish_arr[board[npx][npy]].alive) { // 살아있는 물고기의 경우
					nx = npx;
					ny = npy;
					return true;
				}
			}
		}
		change_direction(fish_num);
	}
}

//  
void move_fish(int target_board[SIZE][SIZE])
{
	// 숫자가 작은 물고기부터
	for (int i = 0; i < 17; i++)
	{
		if (fish_arr[i].alive) // 살아있는 물고기의 경우
		{
			int fcx = fish_arr[i].fx;
			int fcy = fish_arr[i].fy;
			int nx = fcx;
			int ny = fcy;
			if (find_next_fish(i, target_board, nx, ny) == true) // 물고기와 바꿀 경우
			{
				// 다음 물고기 위치를 다음칸으로 변경
				fish_arr[target_board[nx][ny]].fx = fish_arr[i].fx;
				fish_arr[target_board[nx][ny]].fy = fish_arr[i].fy;
			}
			swap(target_board[nx][ny], target_board[fcx][fcy]);
			fish_arr[i].fx = nx;
			fish_arr[i].fy = ny;
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
	
	// 상어 칸에 해당하는 물고기 먹힘
	fish_arr[board_cpy[shark_x][shark_y]].alive = false;
	board_cpy[shark_x][shark_y] = SHARK;

	move_fish(board_cpy);
	vector<pair<int, int>> shark_positions = get_next_shark_positions(board_cpy, shark_x, shark_y, shark_direction);
	if (shark_positions.size() == 0) // 먹을 물고기가 없을 경우
	{
		cout << score << endl;
		if (score > max_score)
		{
			max_score = score;
			return;
		}
	}
	for (int i = 0; i < shark_positions.size(); i++)
	{
		int shark_nx = shark_positions[i].first;
		int shark_ny = shark_positions[i].second;
		int shark_nd = fish_arr[board_cpy[shark_nx][shark_ny]].direction;
		board_cpy[shark_x][shark_y] = 0;
		solve(board_cpy, score + board_cpy[shark_nx][shark_ny], shark_nx, shark_ny, shark_nd);
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
	solve(board_init, board_init[0][0], 0, 0, fish_arr[board_init[0][0]].direction);
	cout << max_score;
	return 0;
}