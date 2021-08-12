#include<stdc++.h>
using namespace std;

int vway[2][4] = { 0,0,1,-1,1,-1,0,0 };
int N, M,zc = 0,cc =0, answer = 0;
vector<pair<int, int> > virus;
void columChoice(vector<vector<int> > &lab,int depth,int from)
{
	if (depth == 3)
	{
		vector<vector<int> > result(N, vector<int>(M));
		result.assign(lab.begin(), lab.end());
		queue<pair<int,int> > q;
		pair<int, int> cur;
		int ny, nx, vc = 0, totalz = M*N -cc - 3 - answer;
		for (int i = 0; i < virus.size(); ++i)
			q.push(virus[i]);
		while (!q.empty())
		{
			if (vc > totalz)
				return;
			cur = q.front();
			q.pop();
			vc++;
			for (int i = 0; i < 4; ++i)
			{
				ny = cur.first + vway[0][i];
				nx = cur.second + vway[1][i];
				if (ny < 0 || nx < 0 || ny >= N || nx >= M || result[ny][nx] >= 1) continue;
				result[ny][nx] = 2;
				q.push({ ny,nx });
			}
		}
		totalz = N * M - cc - 3 - vc;
		answer = answer > totalz ? answer : totalz;
		return;
	}
	int fromy = from / M;
	int fromx = from % M;
	for (int i = fromy; i < N; ++i)
	{
		for (int j = fromx; j < M; ++j)
		{
			if (lab[i][j] != 0) continue;
			lab[i][j] = 8;
			columChoice(lab, depth + 1, i*M + j);
			lab[i][j] = 0;
		}
		fromx = 0;
	}
}


int main()
{
	scanf("%d %d", &N, &M);
	vector<vector<int> > lab(N, vector<int>(M));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
		{
			scanf(" %d", &lab[i][j]);
			if (lab[i][j] == 0)
				zc++;
			else if (lab[i][j] == 2)
				virus.push_back({ i,j });
			else
				cc++;
		}
	}
	columChoice(lab, 0, 0);
	printf("%d", answer);
	return 0;
}
