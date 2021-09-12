// 2048 (Easy)
// https://www.acmicpc.net/problem/12100

#include <iostream>
#include <cstring>

#define MAX 20
using namespace std;

int N = 0;
int block[MAX][MAX];
int max_result = 0;

void print_block()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << block[i][j] << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}

int get_max_block()
{
	int result = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			result = result > block[i][j] ? result : block[i][j];
		}
	}
	return result;
}

void move_right()
{
	for (int i = 0; i < N; i++)
	{
		int ptr_pos = N - 1; // 합쳐진 블록 위치
		int ptr_cur = N - 1;
		while (true) 
		{
			if (ptr_cur < 0) break;
			if (block[i][ptr_cur]) // 현재 위치에 블록이 있을 경우
			{
				bool flag = true; // 값을 못찾은 경우, 방향으로 밀어주기
				for (int j = ptr_cur - 1; j >= 0; j--)
				{
					if (block[i][j] == block[i][ptr_cur]) // 다음 블록 값이 현재 값과 같을 경우
					{
						int sum_value = block[i][ptr_cur] * 2;
						block[i][j] = 0;
						block[i][ptr_cur] = 0;
						block[i][ptr_pos] = sum_value;
						flag = false;
						break;
					}
					if (block[i][j] && block[i][ptr_cur] != block[i][j]) // 탐색 중 숫자가 다른 블록을 만난 경우
					{
						break;
					}
				}
				if (flag && ptr_pos != ptr_cur)
				{
					block[i][ptr_pos] = block[i][ptr_cur];
					block[i][ptr_cur] = 0;
				}
				ptr_cur--;
				ptr_pos--;
			}
			else
			{
				ptr_cur--;
			}
		}
	}
}

void move_left()
{
	for (int i = 0; i < N; i++)
	{
		int ptr_pos = 0;
		int ptr_cur = 0;
		while (true)
		{
			if (ptr_cur > N - 1) break;
			if (block[i][ptr_cur]) // 현재 위치에 블록이 있을 경우
			{
				bool flag = true; // 값을 못찾은 경우, 방향으로 밀어주기
				for (int j = ptr_cur + 1; j < N; j++)
				{
					if (block[i][j] == block[i][ptr_cur]) // 다음 블록 값이 현재 값과 같을 경우
					{
						int sum_value = block[i][ptr_cur] * 2;
						block[i][j] = 0;
						block[i][ptr_cur] = 0;
						block[i][ptr_pos] = sum_value;
						flag = false;
						break;
					}
					if (block[i][j] && block[i][ptr_cur] != block[i][j]) // 탐색 중 숫자가 다른 블록을 만난 경우
					{
						break;
					}
				}
				if (flag && ptr_pos != ptr_cur)
				{
					block[i][ptr_pos] = block[i][ptr_cur];
					block[i][ptr_cur] = 0;
				}
				ptr_cur++;
				ptr_pos++;
			}
			else
			{
				ptr_cur++;
			}
		}
	}
}

void move_down()
{
	for (int i = 0; i < N; i++)
	{
		int ptr_cur = N - 1;
		int ptr_pos = N - 1;
		while (true)
		{
			if (ptr_cur < 0) break;
			if (block[ptr_cur][i])
			{
				bool flag = true; // 값을 못찾은 경우, 방향으로 밀어주기
				for (int j = ptr_cur - 1; j >= 0; j--)
				{
					if (block[j][i] == block[ptr_cur][i])
					{
						int sum_value = block[ptr_cur][i] * 2;
						block[j][i] = 0;
						block[ptr_cur][i] = 0;
						block[ptr_pos][i] = sum_value;
						flag = false;
						break;
					}
					if (block[j][i] && block[j][i] != block[ptr_cur][i])
					{
						break;
					}
				}
				if (flag && ptr_pos != ptr_cur)
				{
					block[ptr_pos][i] = block[ptr_cur][i];
					block[ptr_cur][i] = 0;
				}
				ptr_cur--;
				ptr_pos--;
			}
			else
			{
				ptr_cur--;
			}
		}
	}
}

void move_up()
{
	for (int i = 0; i < N; i++)
	{
		int ptr_cur = 0;
		int ptr_pos = 0;
		while (true)
		{
			if (ptr_cur > N - 1) break;
			if (block[ptr_cur][i])
			{
				bool flag = true; // 값을 못찾은 경우, 방향으로 밀어주기
				for (int j = ptr_cur + 1; j < N; j++)
				{
					if (block[j][i] == block[ptr_cur][i])
					{
						int sum_value = block[ptr_cur][i] * 2;
						block[j][i] = 0;
						block[ptr_cur][i] = 0;
						block[ptr_pos][i] = sum_value;
						flag = false;
						break;
					}
					if (block[j][i] && block[j][i] != block[ptr_cur][i])
					{
						break;
					}
				}
				if (flag && ptr_pos != ptr_cur)
				{
					block[ptr_pos][i] = block[ptr_cur][i];
					block[ptr_cur][i] = 0;
				}
				ptr_cur++;
				ptr_pos++;
			}
			else
			{
				ptr_cur++;
			}
		}
	}
}

void move_block(int direction) // 0: 동, 1: 서, 2: 남, 3: 북
{
	if (direction == 0)
	{
		move_right();
		return;
	}
	if (direction == 1) {
		move_left();
		return;
	}
	if (direction == 2) {
		move_down();
		return;
	}
	if (direction == 3){
		move_up();
		return;
	}
}

void dfs(int level)
{
	if (level == 5)
	{
		int result = get_max_block();
		max_result = max_result > result ? max_result : result;
		return;
	}
	int block_cpy[MAX][MAX] = { 0, };
	memcpy(block_cpy, block, sizeof(block));
	for (int i = 0; i < 4; i++)
	{
		move_block(i);
		dfs(level + 1);
		memcpy(block, block_cpy, sizeof(block));
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> block[i][j];
		}
	}
	
	dfs(0);
	cout << max_result << '\n';
	return 0;
}