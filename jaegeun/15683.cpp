// ����
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
	int x; // x��ǥ
	int y; // y��ǥ
	int cam_num; // ī�޶� ����
}cam_pos;

typedef struct
{
	int d[4]; // ī�޶� �����ϴ� ����
}cam_view;

int N = 0, M = 0; // ����, ����
int min_cnt = 21e8;

deque<cam_pos> cam_q; // ī�޶� ��ġ, ����
vector<vector<cam_view>> cam_status(6); // ī�޶��� ������ ����

int office_init[SIZE][SIZE] = { 0, };
int office_final[SIZE][SIZE] = { 0, };

//		     �� �� �� ��
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };
int used_cam_status[10] = { 0, }; // Ž���� ī�޶� ����

// ���� �簢���� ���
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

void print_office() // �׽�Ʈ�� �繫�� ����
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

// ī�޶��� ������ �޾� �繫�� ä��
// office : ���� �繫�� ����
// dst : ���ο� �繫�� ����
// c : ī�޶��� ��ġ, ����
// cam_stat : ī�޶��� ����
void fill_office(int office[SIZE][SIZE], int dst[SIZE][SIZE], cam_pos c, int cam_stat)
{
	for (int j = 0; j < 4; j++) // �� �� �� ��
	{
		if (cam_status[c.cam_num][cam_stat].d[j]) // ī�޶� �ش� ������ Ž���� ���
		{
			int nx = c.x + dx[j];
			int ny = c.y + dy[j];

			while (true)
			{
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) break; // �ε��� ���� �ƿ�
				if (office[nx][ny] == WALL) break; // ��
				if (1 <= office[nx][ny] && office[nx][ny] <= 5) // �ٸ� ī�޶� ���� -> !!**���� ĭ���� �Ѿ**!!
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

// ī�޶��� ��� ��� Ž��, ���̰� ī�޶��� ������ ������ ���, ��� ���
// level : Ž���� ī�޶� ����
// before : ���� �繫�� ����
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

// ī�޶� �ʱ�ȭ
void init_cam_status()
{
	cam_status[1].push_back({ 1, 0, 0, 0 }); // ��  ��  ��
	cam_status[1].push_back({ 0, 1, 0, 0 }); // ��
	cam_status[1].push_back({ 0, 0, 1, 0 }); // ��
	cam_status[1].push_back({ 0, 0, 0, 1 }); // ��

	cam_status[2].push_back({ 1, 0, 1, 0 }); // ���
	cam_status[2].push_back({ 0, 1, 0, 1 }); // ���

	cam_status[3].push_back({ 1, 1, 0, 0 }); // ���
	cam_status[3].push_back({ 0, 1, 1, 0 }); // ���
	cam_status[3].push_back({ 0, 0, 1, 1 }); // ���
	cam_status[3].push_back({ 1, 0, 0, 1 }); // ���

	cam_status[4].push_back({ 1, 1, 1, 0 }); // ����
	cam_status[4].push_back({ 0, 1, 1, 1 }); // ����
	cam_status[4].push_back({ 1, 0, 1, 1 }); // ����
	cam_status[4].push_back({ 1, 1, 0, 1 }); // ����

	cam_status[5].push_back({ 1, 1, 1, 1 }); // �� �� �� ��
}

int main()
{
	memset(used_cam_status, -1, sizeof(used_cam_status));
	init_cam_status();
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M;

	// 0 ��ĭ , 1~5 CCTV, 6 ��
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int inp = 0;
			cin >> inp;
			office_init[i][j] = inp;
			if (1 <= inp && inp <= 5)
				cam_q.push_back({ i, j, inp }); // ī�޶� ť�� ����
		}
	}

	run(0, office_init);
	cout << min_cnt;
	return 0;
}
