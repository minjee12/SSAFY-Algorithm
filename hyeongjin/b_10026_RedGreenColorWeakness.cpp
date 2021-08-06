#include<stdc++.h>
using namespace std;
int N,cresult,nresult;
vector<vector<int> > board;
vector<vector<int> > colorWeakSection;
vector<vector<int> > normalSection;
int access[2][4] = { 0,0,1,-1,1,-1,0,0 };
void normalBFS(){
	int sectionNum = 0, curcolor = 0,ny,nx;
	pair<int, int> ptmp;
	queue<pair<int, int> >q;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (normalSection[i][j] != 0)
				continue;
			q.push({ i,j });
			curcolor = board[i][j];
			sectionNum++;
			normalSection[i][j] = sectionNum;
			while (!q.empty())
			{
				ptmp = q.front();
				q.pop();
				for (int k = 0; k < 4; ++k)
				{
					ny = ptmp.first + access[0][k];
					nx = ptmp.second + access[1][k];
					if (nx >= 0 && nx < N && ny >= 0 && ny < N && normalSection[ny][nx] == 0)
					{
						if (board[ny][nx] == curcolor)
						{
							q.push({ ny,nx });
							normalSection[ny][nx] = sectionNum;
						}
					}
				}
			}
		}
	}
	nresult = sectionNum;
}
void colorweakBFS(){
	int sectionNum = 0, curcolor = 0, ny, nx;
	pair<int, int> ptmp;
	queue<pair<int, int> >q;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (colorWeakSection[i][j] != 0)
				continue;
			q.push({ i,j });
			curcolor = board[i][j];
			sectionNum++;
			colorWeakSection[i][j] = sectionNum;
			while (!q.empty())
			{
				ptmp = q.front();
				q.pop();
				for (int k = 0; k < 4; ++k)
				{
					ny = ptmp.first + access[0][k];
					nx = ptmp.second + access[1][k];
					if (nx >= 0 && nx < N && ny >= 0 && ny < N && colorWeakSection[ny][nx] == 0)
					{
						if ((curcolor == 0 && board[ny][nx] == 0) || (curcolor != 0 && board[ny][nx] != 0))
						{
							q.push({ ny,nx });
							colorWeakSection[ny][nx] = sectionNum;
						}
					}
				}
			}
		}
	}
	cresult = sectionNum;
}
int main()
{
	scanf("%d", &N);
	char inchar;
	vector<int> tmp(N);
	for (int i = 0; i < N; ++i) {
		board.push_back(tmp);
		colorWeakSection.push_back(tmp);
		normalSection.push_back(tmp);
	}
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			scanf(" %c", &inchar);
			if (inchar == 'R')
				board[i][j] = 1;
			else if (inchar == 'G')
				board[i][j] = 2;
		}
	}
	normalBFS();
	colorweakBFS();
	printf("%d %d", nresult, cresult);
	return 0;
}
