// 상어 초등학교
// https://www.acmicpc.net/problem/21608

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

#define SIZE 20
#define EMPTY 0
#define endl '\n'

typedef struct {
	int stuNum;
	int pref[4];
	int final_x;
	int final_y;
}stu;
using namespace std;

int N = 0;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int Class[SIZE][SIZE] = { 0, };

vector<stu> stu_q;

// Class[x][y]에서 s의 선호 학생 수 반환
int find_pref(stu s, int x, int y)
{
	int pref_num = 0;
	for (int d = 0; d < 4; d++)
	{
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < N)
		{
			for (int i = 0; i < 4; i++)
			{
				if (s.pref[i] == Class[nx][ny]) pref_num++;
			}
		}
	}
	return pref_num;
}

// Class[x][y]에서 주변 빈 자리 수 계산
int find_empty(int x, int y)
{
	int empty_num = 0;
	for (int d = 0; d < 4; d++)
	{
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < N)
		{
			if (Class[nx][ny] == EMPTY) empty_num++;
		}
	}
	return empty_num;
}

// 조건 2, 3에 해당하는 칸을 x, y에 저장
void calc_empty(vector<pair<int, int>> pos, int& x, int& y)
{
	int max_empty = 0;
	int board[SIZE][SIZE] = { 0, }; // 주변 빈 자리 개수 저장 배열
	memset(board, -1, sizeof(board));
	for (int i = 0; i < pos.size(); i++)
	{
		int px = pos[i].first;
		int py = pos[i].second;
		int empty = find_empty(px, py);
		board[px][py] = empty;
		if (empty >= max_empty)
		{
			max_empty = empty;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] == max_empty) // 조건 3 
			{
				x = i;
				y = j;
				return;
			}
		}
	}
}

// 빈 칸에서 해당 학생의 선호학생 수를 담은 vector 반환
vector< pair<int, int>> calc_pref(stu s)
{
	vector< pair<int, int>> pref_pos;
	int board[SIZE][SIZE] = { 0, }; // 주변 선호 학생 개수 저장 배열
	memset(board, -1, sizeof(board));
	int max_pref = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Class[i][j] == EMPTY) { // 빈칸
				int pref = find_pref(s, i, j);
				board[i][j] = pref;
				if (pref > max_pref)
					max_pref = pref;
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] == max_pref)
			{
				pref_pos.push_back(make_pair(i, j));
			}
		}
	}
	return pref_pos;
}

void solve()
{
	for(int i = 0; i < stu_q.size(); i++){
		int ax = 0;
		int ay = 0;
		vector< pair<int, int>> pos = calc_pref(stu_q[i]);
		
		if (pos.size() > 1) { // 조건 1을 만족하는 칸이 1개 이상일 경우
			calc_empty(pos, ax, ay); // 조건 2
		}
		else { // 조건 1을 만족하는 칸이 1개일 경우
			ax = pos[0].first;
			ay = pos[0].second;
		}
		Class[ax][ay] = stu_q[i].stuNum;
		stu_q[i].final_x = ax;
		stu_q[i].final_y = ay;
	}

	int score = 0;
	for (int i = 0; i < stu_q.size(); i++) {
		int result = find_pref(stu_q[i], stu_q[i].final_x, stu_q[i].final_y);
		if (result == 0) continue;
		score += int(pow(10, result - 1));
	}
	cout << score;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N * N; i++)
	{
		int stu, a, b, c, d;
		cin >> stu >> a >> b >> c >> d;
		stu_q.push_back({ stu, a, b, c, d });
	}
	solve();
	return 0;
}