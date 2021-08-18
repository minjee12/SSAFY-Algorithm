// 상어 초등학교
// https://www.acmicpc.net/problem/21608

#include <iostream>
#include <queue>

#define SIZE 20
#define EMPTY 0
#define endl '\n'

typedef struct {
	int stuNum;
	int pref[4];
}stu_pref;
using namespace std;

int N = 0;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int Class[SIZE][SIZE] = { 0, };

vector<stu_pref> stu_q;

// 빈 자리가 제일 많은 칸 탐색
// 맨 마지막부터 탐색할 경우, 가장 작은 행, 열을 찾을 수 있음
void calc_empty(stu_pref stu, vector<pair<int, int>> pos, int& x, int& y)
{
	int max_empty = 0;

	int board[SIZE][SIZE] = { 0, }; // 주변 빈 자리 개수 저장 배열
	for (int i = 0; i < pos.size(); i++)
	{
		int empty = 0;
		int px = pos[i].first;
		int py = pos[i].second;

		for (int d = 0; d < 4; d++)
		{
			int nx = dx[d] + px;
			int ny = dy[d] + py;
			if (0 <= nx && nx < N && 0 <= ny && ny < N && Class[nx][ny] == EMPTY)
				empty++;
		}
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
			if (board[i][j] == max_empty)
			{
				x = i;
				y = j;
				return;
			}
		}
	}
}

vector< pair<int, int>> calc_pref(stu_pref stu)
{
	vector< pair<int, int>> pref_pos;
	int board[SIZE][SIZE] = { 0, }; // 주변 선호 학생 개수 저장 배열
	int max_pref = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Class[i][j] == EMPTY) { // 빈칸
				int pref = 0;
				for (int d = 0; d < 4; d++)
				{
					int nx = dx[d] + i;
					int ny = dy[d] + j;
					if (0 <= nx && nx < N && 0 <= ny && ny < N)
					{
						for (int p = 0; p < 4; p++)
						{
							if (stu.pref[p] == Class[nx][ny])
								pref++;
						}
					}
				}
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
		stu_pref a = stu_q[i];
		int ax = 0;
		int ay = 0;
		vector< pair<int, int>> pos = calc_pref(a);
		// 조건 2
		if (pos.size() > 1) {
			calc_empty(a, pos, ax, ay);
		}
		else {
			Class[pos[0].first][pos[0].second] = a.stuNum;
			continue;
		}
		//cout << ax << " " << ay << endl;
		Class[ax][ay] = a.stuNum;
	}
	
	//for (int i = 0; i < N; i++)
	//{
	//	for (int j = 0; j < N; j++)
	//	{
	//		cout << Class[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	int score = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int s = 0; s < stu_q.size(); s++)
			{
				if (Class[i][j] == stu_q[s].stuNum)
				{
					int pref = 0;
					for (int d = 0; d < 4; d++)
					{
						int nx = dx[d] + i;
						int ny = dy[d] + j;
						if (0 <= nx && nx < N && 0 <= ny && ny < N)
						{
							for (int p = 0; p < 4; p++)
							{
								if (stu_q[s].pref[p] == Class[nx][ny])
									pref++;
							}
						}
					}
					if (pref == 4) score += 1000;
					else if (pref == 3) score += 100;
					else if (pref == 2) score += 10;
					else if (pref == 1) score += 1;
				}
			}
		}
	}
	cout << score;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	N;
	for (int i = 0; i < N * N; i++)
	{
		int stu, a, b, c, d;
		cin >> stu >> a >> b >> c >> d;
		stu_q.push_back({ stu, a, b, c, d });
	}
	solve();
	/*while (stu_q.size())
	{
		
	}*/
	return 0;
}