#include<stdc++.h>
using namespace std;
int access[2][4] = { -1,0,1,0,0,1,0,-1 };
vector<pair<int, int> > camlist;
int N, M,camcnt,result = 987654321;
void searchall(vector<vector<int> >& o,int depth)
{
	int cnt, ny, nx;
	if (depth == camcnt)
	{
		cnt = 0;
		for (int i = 0; i < o.size(); ++i)
		{
			for (int j = 0; j < o[i].size(); ++j)
			{
				if (o[i][j] == 0)
					cnt++;
			}
		}
		result = (result < cnt ? result : cnt);
		return;
	}
	int camtype = o[camlist[depth].first][camlist[depth].second];
	vector<pair<int, int> > cansearch;

	if (camtype == 5)
	{
		for (int i = 0; i < 4; ++i)													   // All way check
		{
			ny = camlist[depth].first + access[0][i];
			nx = camlist[depth].second + access[1][i];
			if (ny >= 0 && nx >= 0 && ny < N && nx < M &&  o[ny][nx] < 6 )
			{
				cansearch.push_back({ ny,nx });
				while (1)
				{
					ny += access[0][i];
					nx += access[1][i];
					if (ny >= 0 && nx >= 0 && ny < N && nx < M && o[ny][nx] < 6)
						cansearch.push_back({ ny,nx });
					else
						break;
				}
			}
		}
		cnt = cansearch.size();
		for (int i = 0; i < cnt; ++i)
		{
			if (o[cansearch[i].first][cansearch[i].second] <= 0)
				o[cansearch[i].first][cansearch[i].second] -= 1;
		}
		searchall(o, depth + 1);
		for (int i = 0; i < cnt; ++i)
		{
			if (o[cansearch[i].first][cansearch[i].second] <= -1)
				o[cansearch[i].first][cansearch[i].second] += 1;
		}
	}
	else if (camtype == 2)
	{
		for (int i = 0; i < 2; ++i)				                                          // 2 different direct way check
		{
			cansearch.clear();
			ny = camlist[depth].first + access[0][i];
			nx = camlist[depth].second + access[1][i];
			if (ny >= 0 && nx >= 0 && ny < N && nx < M && o[ny][nx] < 6)
			{
				cansearch.push_back({ ny,nx });
				while (1)
				{
					ny += access[0][i];
					nx += access[1][i];
					if (ny >= 0 && nx >= 0 && ny < N && nx < M && o[ny][nx] < 6)
						cansearch.push_back({ ny,nx });
					else
						break;
				}
			}

			ny = camlist[depth].first + access[0][i + 2];
			nx = camlist[depth].second + access[1][i + 2];
			if (ny >= 0 && nx >= 0 && ny < N && nx < M && o[ny][nx] < 6)
			{
				cansearch.push_back({ ny,nx });
				while (1)
				{
					ny += access[0][i + 2];
					nx += access[1][i + 2];
					if (ny >= 0 && nx >= 0 && ny < N && nx < M && o[ny][nx] < 6)
						cansearch.push_back({ ny,nx });
					else
						break;
				}
			}
			cnt = cansearch.size();
			for (int i = 0; i < cnt; ++i)
			{
				if (o[cansearch[i].first][cansearch[i].second] <= 0)
					o[cansearch[i].first][cansearch[i].second] -= 1;
			}
			searchall(o, depth + 1);
			for (int i = 0; i < cnt; ++i)
			{
				if (o[cansearch[i].first][cansearch[i].second] <= -1)
					o[cansearch[i].first][cansearch[i].second] += 1;
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			cansearch.clear();
			if (camtype == 1)
			{
				ny = camlist[depth].first + access[0][i];
				nx = camlist[depth].second + access[1][i];
				if (ny >= 0 && nx >= 0 && ny < N && nx < M && o[ny][nx] < 6)
				{
					cansearch.push_back({ ny,nx });
					while (1)
					{
						ny += access[0][i];
						nx += access[1][i];
						if (ny >= 0 && nx >= 0 && ny < N && nx < M && o[ny][nx] < 6)
							cansearch.push_back({ ny,nx });
						else
							break;
					}
				}
			}
			else 
			{
				for (int j = 0; j < camtype-1; j++)
				{
					ny = camlist[depth].first + access[0][(i + j) % 4];
					nx = camlist[depth].second + access[1][(i + j) % 4];
					if (ny >= 0 && nx >= 0 && ny < N && nx < M && o[ny][nx] < 6)
					{
						cansearch.push_back({ ny,nx });
						while (1)
						{
							ny += access[0][(i + j) % 4];
							nx += access[1][(i + j) % 4];
							if (ny >= 0 && nx >= 0 && ny < N && nx < M &&  o[ny][nx] < 6)
								cansearch.push_back({ ny,nx });
							else
								break;
						}
					}
				}
			}
			cnt = cansearch.size();
			for (int i = 0; i < cnt; ++i)
			{
				if (o[cansearch[i].first][cansearch[i].second] <= 0)
					o[cansearch[i].first][cansearch[i].second] -= 1;
			}
			searchall(o, depth + 1);
			for (int i = 0; i < cnt; ++i)
			{
				if (o[cansearch[i].first][cansearch[i].second] <= -1)
					o[cansearch[i].first][cansearch[i].second] += 1;
			}
		}
	}

}
int main()
{
	int tmp;
	scanf("%d %d", &N, &M);
	vector<vector<int> > office(N, vector<int>(M));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			scanf(" %d", &tmp);
			if (tmp >= 1 && tmp < 6)
				camlist.push_back({ i,j });
			office[i][j] = tmp;
		}
	}
	camcnt = camlist.size();
	searchall(office, 0);
	printf("%d", result);
	return 0;
}
