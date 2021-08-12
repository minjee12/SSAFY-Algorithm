// 뱀
// https://www.acmicpc.net/problem/3190

#include <iostream>
#include <queue>

#define SIZE 100 + 1
#define EMPTY 0
#define APPLE 1
#define SNAKE 8

using namespace std;

typedef struct
{
	int x;
	int y;
}Pos;

int N = 0; // 보드 크기
int K = 0; // 사과 개수
int L = 0; // 방향 변환 횟수

//			  동 남  서  북
int dx[] = { 0,  1,  0, -1 };
int dy[] = { 1,  0, -1,  0 };

int cur_direct = 0;

Pos head = { 0, 0 }; // 머리 위치

int board[SIZE][SIZE] = { 0, };

queue<Pos> tail; // 꼬리 큐
queue<pair<int, char>> dq;

void print_board()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << "==========================" << endl;
}

//종료되면 fasle 리턴
bool move()
{
	//print_board();
	// 몸 길이를 늘려 머리를 다음칸에 위치시킴
	int nx = head.x + dx[cur_direct];
	int ny = head.y + dy[cur_direct];
	if (nx < 0 || N <= nx || ny < 0 || N <= ny) // 범위 밖으로 나감
	{
		//cout << "벽" << endl;
		return false;
	}
	if (board[nx][ny] == SNAKE) // 자기 몸에 부딪힘
	{
		//cout << "몸" << endl;
		return false;
	}
	// 머리 위치 바꾸기
	tail.push({ head.x, head.y });

	// 다음 칸이 사과라면
	if (board[nx][ny] == APPLE)
	{
		// 사과가 없어지고 꼬리는 움직이지 않음
		board[nx][ny] = SNAKE;
		head.x = nx;
		head.y = ny;
		return true;
	}
	else // 사과가 없다면
	{
		board[nx][ny] = SNAKE;
		head.x = nx;
		head.y = ny;
		// 꼬리가 위치한 칸을 비워준다
		board[tail.front().x][tail.front().y] = EMPTY;
		tail.pop();
		return true;
	}
}

void change_direction(char d)
{
	if (d == 'D')
	{
		cur_direct = (cur_direct + 1) % 4;
	}
	else
	{
		cur_direct--;
		if (cur_direct < 0)
		{
			cur_direct = 3;
		}
	}
	//cout << endl << "===== 현재 방향 =====" << endl << cur_direct << endl;
}

int main()
{
	int cnt = 0;
	//freopen_s(new FILE*, "text.txt", "r", stdin);
	board[0][0] = SNAKE;

	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++)
	{
		int ax, ay;
		cin >> ax >> ay;
		board[ax - 1][ay - 1] = APPLE;
	}

	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int step;
		char d;
		cin >> step >> d;
		dq.push(make_pair(step, d));
	}

	while (true)
	{
		if (dq.size()) {
			if (cnt == dq.front().first)
			{
				change_direction(dq.front().second);
				dq.pop();
			}
		}
		if (move() == false)
			break;
		cnt++;
	}
	cout << cnt + 1;
	return 0;
}