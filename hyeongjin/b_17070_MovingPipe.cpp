#include<stdc++.h>
using namespace std;

int N,cnt=0;
struct Pipe{
	int way; // 3 - diagonal, 0 - width , 1 - height
	int tx, ty, hx, hy;
};
int access[2][3] = { 1,0,1,0,1,1 };


void pushingPipe(Pipe p, vector<vector<int> >& arr)
{
	if (p.hx == N - 1 && p.hy == N - 1)
	{
		cnt++;
		return;
	}
	for (int i = 0; i < 3; ++i)
	{
		if (i == p.way) continue;
		int nx = p.hx + access[0][i];
		int ny = p.hy + access[1][i];
		if (ny >= N || nx >= N || arr[nx][ny] == 1 ) continue;
		if (i == 2)
		{
			if (p.hx + access[0][0] >= N || p.hy + access[1][0] >= N || arr[p.hx + access[0][0]][p.hy + access[1][0]] == 1) continue;
			if (p.hx + access[0][1] >= N || p.hy + access[1][1] >= N || arr[p.hx + access[0][1]][p.hy + access[1][1]] == 1) continue;
		}
		int nway;
		if (p.hx != nx && p.hy != ny)
			nway = 3;
		else if (p.hx == nx)
			nway = 0;
		else
			nway = 1;
		Pipe np = {nway,p.hx,p.hy,nx,ny};
		pushingPipe(np, arr);
	}
}
int main() {
	scanf("%d", &N);
	vector<vector<int> > arr ( N, vector<int>(N));
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) scanf(" %d", &arr[i][j]);
	Pipe pipe({ 0,0,0,0,1 });
	pushingPipe(pipe, arr);
	printf("%d", cnt);
	return 0;
}
