// ⚾
// https://www.acmicpc.net/problem/17281

#include <iostream>
#include <bitset>
#define MAX 51

using namespace std;

int N = 0;
int max_score = 0;
int seq[9];
int used[10] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
int game_board[MAX][10];

void play_game()
{
	int score = 0;
	int cur_player = 0;
	for (int i = 0; i < N; i++) {
		int out_cnt = 0;
		bitset<4> base;
		base.reset();
		// 이닝 시작
		while (out_cnt < 3) {
			int result = game_board[i][seq[cur_player]];
			if (result == 0) { // 아웃
				out_cnt++;
			}
			else {
				base[0] = 1;
				// 비트셋 밀면서 진행
				// base 3		2		1		0
				//		3루		2루		1루		홈
				for (int j = 4 - result; j < 4; j++)
				{
					if (base.test(j)) score++;
				}
				base <<= result;
			}
			cur_player++;
			if (cur_player == 9) cur_player = 0;
		}
	}
	if (score > max_score)
	{
		max_score = score;
	}
}

void set_seq(int level)
{
	if (level == 3)
	{
		seq[level] = 1;
		set_seq(level + 1);
	}
	if (level == 9)
	{
		play_game();
		return;
	}
	for (int i = 2; i < 10; i++)
	{
		if (!used[i])
		{
			seq[level] = i;
			used[i] = 1;
			set_seq(level + 1);
			used[i] = 0;
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			cin >> game_board[i][j];
		}
	}
	set_seq(0);
	cout << max_score << "\n";
	return 0;
}