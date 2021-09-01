// 탈출
// https://www.acmicpc.net/problem/3055

#pragma warning (disable:4996)
#include <iostream>
#include <queue>

#define MAX 51
#define HEDGEHOG 0 // 고슴도치
#define WATER 1 // 물
using namespace std;

typedef struct {
	int x;
	int y;
	int state;
}node;

int R = 0, C = 0;
int bb_x = 0, bb_y = 0; // 비버굴 위치

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

char tittub[MAX][MAX];
int visited[2][MAX][MAX];

int bfs(node hg, vector<node> vect_wt)
{
	queue<node> q;
	for (int i = 0; i < vect_wt.size(); i++)
	{
		q.push(vect_wt[i]);
		visited[WATER][vect_wt[i].x][vect_wt[i].y] = 1;
	}
	q.push(hg);
	visited[HEDGEHOG][hg.x][hg.y] = 1;
	while (q.size())
	{
		node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];

			if (nx < 0 || nx > R - 1 || ny < 0 || ny > C - 1) continue; // 범위 아웃
			if (tittub[nx][ny] == 'X') continue; // 돌
			if (now.state == WATER && tittub[nx][ny] == 'D')continue; // 물은 비버굴로 이동 불가
			if (visited[now.state][nx][ny]) continue; // 방문기록 있음
			if (now.state == HEDGEHOG)
			{
				// 물이 참
				if (visited[WATER][nx][ny]) continue;
				// 비버 굴
				if (tittub[nx][ny] == 'D') {
					return visited[HEDGEHOG][now.x][now.y];
				}
				q.push({ nx, ny, HEDGEHOG });
				visited[HEDGEHOG][nx][ny] = visited[HEDGEHOG][now.x][now.y] + 1;
			}
			if (now.state == WATER)
			{
				q.push({ nx, ny, WATER });
				visited[WATER][nx][ny] = 1;
			}
		}
	}
	return 0;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int hg_x = 0, hg_y = 0;
	vector<node> vect_water;
	scanf("%d %d", &R, &C);
	
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			scanf(" %c", &tittub[i][j]);
			if (tittub[i][j] == 'S') // 고슴도치 위치
			{
				hg_x = i; hg_y = j;
			}
			else if (tittub[i][j] == 'D') // 비버굴 위치
			{
				bb_x = i; bb_y = j;
			}
			else if (tittub[i][j] == '*')
			{
				vect_water.push_back({ i, j, WATER });
			}
		}
	}

	int result = bfs({ hg_x, hg_y, HEDGEHOG }, vect_water);
	if (result)	printf("%d\n", result);
	else printf("KAKTUS\n");
	return 0;
}