// 감시
// https://www.acmicpc.net/problem/15683

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <cstring>

#define SIZE 8
#define BLIND 0
#define WALL 6
#define OBSERVE 8

using namespace std;

typedef struct
{
	int x; // x좌표
	int y; // y좌표
	int cam_num; // 카메라 종류
}cam_pos;

typedef struct
{
	int d[4]; // 카메라가 감시하는 방향
}cam_view;

int N = 0, M = 0; // 세로, 가로
int min_cnt = 21e8;

deque<cam_pos> cam_q; // 카메라 위치, 종류
vector<vector<cam_view>> cam_status(6); // 카메라의 가능한 상태

int office_init[SIZE][SIZE] = { 0, };
int office_final[SIZE][SIZE] = { 0, };

//		     동 북 서 남
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };
int used_cam_status[10] = { 0, }; // 탐색된 카메라 상태

// 최종 사각지대 계산
int cnt_blind()
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (office_final[i][j] == BLIND)
				cnt++;
		}
	}
	return cnt;
}

void print_office() // 테스트용 사무실 찍어보기
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << office_final[i][j] << " ";
		}
		cout << endl;
	}
	cout << "==================" << endl;
}

// 카메라의 종류를 받아 사무실 채움
// office : 이전 사무실 상태
// dst : 새로운 사무실 상태
// c : 카메라의 위치, 종류
// cam_stat : 카메라의 상태
void fill_office(int office[SIZE][SIZE], int dst[SIZE][SIZE], cam_pos c, int cam_stat)
{
	for (int j = 0; j < 4; j++) // 동 서 남 북
	{
		if (cam_status[c.cam_num][cam_stat].d[j]) // 카메라가 해당 방향을 탐색할 경우
		{
			int nx = c.x + dx[j];
			int ny = c.y + dy[j];

			while (true)
			{
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) break; // 인덱스 범위 아웃
				if (office[nx][ny] == WALL) break; // 벽
				if (1 <= office[nx][ny] && office[nx][ny] <= 5) // 다른 카메라 만남 -> !!**다음 칸으로 넘어감**!!
				{
					nx = nx + dx[j];
					ny = ny + dy[j];
					continue;
				}
				dst[nx][ny] = OBSERVE;

				nx = nx + dx[j];
				ny = ny + dy[j];
			}
		}
	}
}

// 카메라의 모든 경우 탐색, 깊이가 카메라의 개수와 같아진 경우, 결과 계산
// level : 탐색한 카메라 개수
// before : 이전 사무실 상태
void run(int level, int before[8][8])
{
	if (level == cam_q.size())
	{
		memcpy(office_final, before, sizeof(office_final));
		//print_office();
		int result = cnt_blind();
		min_cnt = min(result, min_cnt);
		return;
	}
	for (int j = 0; j < cam_status[cam_q[level].cam_num].size(); j++)
	{
		int cpy_office[8][8] = { 0, };
		memcpy(cpy_office, before, sizeof(office_init));
		fill_office(before, cpy_office, cam_q[level], j);

		used_cam_status[level] = j;
		run(level + 1, cpy_office);
		used_cam_status[level] = -1;
	}
}

// 카메라 초기화
void init_cam_status()
{
	cam_status[1].push_back({ 1, 0, 0, 0 }); // →  ←  ↓
	cam_status[1].push_back({ 0, 1, 0, 0 }); // ↑
	cam_status[1].push_back({ 0, 0, 1, 0 }); // ←
	cam_status[1].push_back({ 0, 0, 0, 1 }); // ↓

	cam_status[2].push_back({ 1, 0, 1, 0 }); // ←→
	cam_status[2].push_back({ 0, 1, 0, 1 }); // ↑↓

	cam_status[3].push_back({ 1, 1, 0, 0 }); // ↑→
	cam_status[3].push_back({ 0, 1, 1, 0 }); // ←↑
	cam_status[3].push_back({ 0, 0, 1, 1 }); // ←↓
	cam_status[3].push_back({ 1, 0, 0, 1 }); // ↓→

	cam_status[4].push_back({ 1, 1, 1, 0 }); // ←↑→
	cam_status[4].push_back({ 0, 1, 1, 1 }); // ←↓↑
	cam_status[4].push_back({ 1, 0, 1, 1 }); // ←↓→
	cam_status[4].push_back({ 1, 1, 0, 1 }); // ↑↓→

	cam_status[5].push_back({ 1, 1, 1, 1 }); // → ↑ ← ↓
}

int main()
{
	memset(used_cam_status, -1, sizeof(used_cam_status));
	init_cam_status();
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;

	// 0 빈칸 , 1~5 CCTV, 6 벽
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int inp = 0;
			cin >> inp;
			office_init[i][j] = inp;
			if (1 <= inp && inp <= 5)
				cam_q.push_back({ i, j, inp }); // 카메라 큐에 삽입
		}
	}

	run(0, office_init);
	cout << min_cnt;
	return 0;
}
