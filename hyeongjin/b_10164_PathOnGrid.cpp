#include<stdc++.h>
using namespace std;

int cango[2][2] = { 1,0,0,1 };
int N, M, K;

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	int x = M-1, y = N-1;
	if (K != 0)
	{
		x = (K-1) % M ;
		y = (K-1) / M;
	}
	vector<vector<int> > grid(N, vector<int>(M));
	//init
	for (int i = 0; i <= y; ++i)
	{
		grid[i][0] = 1;
	}
	for (int i = 0; i <= x; ++i)
	{
		grid[0][i] = 1;
	}
	//counting To O point
	for (int i = 1; i <= y; ++i) {
		for (int j = 1; j <= x;++j)
		{
			grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
		}
	}
	//init from 0 point to end point
	for (int i = y; i < N; ++i)
	{
		grid[i][x] = grid[y][x];
	}
	for (int i = x; i < M; ++i)
	{
		grid[y][i] = grid[y][x];
	}		  
	//counting from 0 point To end point
	for (int i = y; i < N; ++i) {
		for (int j = x; j < M; ++j)
		{
			grid[i][j] = 0;
			if (i > 0)
				grid[i][j] += grid[i - 1][j];
			if ( j > 0)
				grid[i][j] += grid[i][j - 1];
		}
	}
	printf("%d", grid[N - 1][M - 1]);
	return 0;
}
