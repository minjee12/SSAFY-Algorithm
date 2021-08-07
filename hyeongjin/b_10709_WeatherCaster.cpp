#include<stdc++.h>
using namespace std;

int main()
{
	int H, W;
	bool crun;
	char inchar;
	scanf("%d %d", &H, &W);
	vector<vector<int> > clouds(H, vector<int> (W,-1));
	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
		{
			scanf(" %c", &inchar);
			if (inchar == 'c')
				clouds[i][j] = 0;
		}
	}
	for (int i = 0; i < H; ++i)
	{
		crun = false;
		for (int j = 0; j < W; ++j)
		{
			if (clouds[i][j] == 0)
				crun = true;
			else if (crun)
				clouds[i][j] = clouds[i][j - 1] + 1 ;
		}
	}
	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
		{
			printf("%d ", clouds[i][j]);
		}
		printf("\n");
	}
	return 0;
}
