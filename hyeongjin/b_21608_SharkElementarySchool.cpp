#include<stdc++.h>
using namespace std;

int N;
int nearby[2][4] = { 0,0,1,-1,1,-1,0,0 };
void candiCheck(int num, vector<vector<int> >& m, vector<vector<int> >& c, vector<set<int> >& l)
{
	int tmp,ny,nx,maxi = -1;
	pair<int, int> result = { 0,0 };
	fill(c.begin(), c.end(), vector<int> (N));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (m[i][j] != 0) continue;
			tmp = 0;
			for (int k = 0; k < 4; ++k)
			{
				ny = i + nearby[0][k];
				nx = j + nearby[1][k];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N ) continue;
				if (m[ny][nx] == 0) // empty
					tmp += 10;
				else
				{
					if (l[num].find(m[ny][nx]) != l[num].end())	   
						tmp += 100;
				}
			}
			if (tmp > maxi)
			{
				result = { i,j };
				maxi = tmp;
			}
		}
	}
	m[result.first][result.second] = num;
}
int main()
{
	int n,num,who[4],answer=0,ny,nx;
	scanf("%d", &N);
	n = N * N;
	vector<set<int> > like(n + 1);
	vector<vector<int> > map(N, vector<int>(N)), candi(N, vector<int>(N));
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d %d %d %d", &num, &who[0], &who[1], &who[2], &who[3]);
		for (int j = 0; j < 4; ++j)
			like[num].emplace(who[j]);

		candiCheck(num, map, candi, like);
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			num = 0;
			for (int k = 0; k < 4; ++k)
			{
				ny = i + nearby[0][k];
				nx = j + nearby[1][k];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
				if (like[map[i][j]].find(map[ny][nx]) != like[map[i][j]].end())
					num++;
			}
			if (num == 4)
				answer += 1000;
			else if (num == 3)
				answer += 100;
			else if (num == 2)
				answer += 10;
			else if (num == 1)
				answer += 1;

		}

	}
	printf("%d", answer);

	return 0;

}

