// 톱니바퀴
// https://www.acmicpc.net/problem/14891

#include <iostream>
#include <deque>
#include <cmath>


#define endl '\n'
#define N 0
#define S 1

using namespace std;

deque<int> gear[4];

void rotate_gear(int gear_index, bool clockwise)
{
	//cout << "회전 기어 : " << gear_index + 1;
	//if (clockwise)
	//{
	//	cout << ", 시계방향 회전" << endl;
	//}
	//else
	//{
	//	cout << ", 반시계방향 회전" << endl;
	//}
	if (clockwise) // 시계방향
	{
		gear[gear_index].push_front(gear[gear_index].back());
		gear[gear_index].pop_back();
	}
	else // 반시계 방향
	{
		gear[gear_index].push_back(gear[gear_index].front());
		gear[gear_index].pop_front();
	}
}

void solve(int inp_gear, bool direction)
{
	// 1. 돌아가는 기어의 왼쪽과 오른쪽 확인
	bool is_rotate[4] = { false, };
	is_rotate[inp_gear] = true;
	// 기준 방향이 홀수일 때, 홀수는 같은 방향으로 회전
	int standard = inp_gear % 2;
	for (int i = inp_gear; i > 0; i--) // 왼쪽 확인
	{
		// i : 기준, is_rotate[i] 가 참이고, 기어의 극이 다르면
		if (is_rotate[i] && gear[i][6] != gear[i - 1][2])
		{
			is_rotate[i - 1] = true;
		}
	}
	for (int i = inp_gear; i < 3; i++) // 오른쪽 확인
	{
		if (is_rotate[i] && gear[i][2] != gear[i + 1][6])
		{
			is_rotate[i + 1] = true;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (is_rotate[i])
		{
			if (i % 2 == standard)
			{
				rotate_gear(i, direction);
			}
			else
			{
				rotate_gear(i, !direction);
			}
		}
	}
	//for (int i = 0; i < 4; i++)
	//{
	//	if (is_rotate[i])
	//	{
	//		cout << "돌아감 ";
	//	}
	//	else {
	//		cout << "안돌아감 ";
	//	}
	//}
	//cout << endl;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int K = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++) {
			char inp;
			cin >> inp;
			gear[i].push_back(int(inp - '0'));
		}
	}

	cin >> K;
	for (int i = 0; i < K; i++) {
		int gear_num, direction;
		cin >> gear_num >> direction;
		if (direction == 1) // 시계방향
		{
			solve(gear_num - 1, true);
		}
		else // 반시계 방향
		{
			solve(gear_num - 1, false);
		}
	}
	int result = 0;
	for (int i = 0; i < 4; i++)
	{
		if (gear[i][0] == S)
		{
			result += pow(2, i);
		}
	}
	cout << result;
	return 0;
}