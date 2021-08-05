#include<stdc++.h>
using namespace std;

int N, M,cur;
queue<pair<int, int> > q;
int access[2][8] = { -1,-1,-1,0,0,1,1,1,-1,0,1,-1,1,-1,0,1 };
int main()
{
	int answer = 0;
	scanf("%d %d", &N, &M);
	vector<vector<int> > ocean(N, vector<int>(M));
	vector<vector<int> > visited(N, vector<int>(M,-1));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			scanf("%d", &ocean[i][j]);
			if (ocean[i][j]) {
				q.push({ i,j });
				visited[i][j] = 0;
			}
		}
	}
	pair<int, int> ptmp;
	while (!q.empty()) {
		ptmp = q.front();
		q.pop();
		cur = visited[ptmp.first][ptmp.second];
		answer = (answer > cur ? answer : cur);
		for (int i = 0; i < 8; ++i)
		{
			if (ptmp.first + access[0][i] >= 0 && ptmp.first + access[0][i] < N && ptmp.second + access[1][i] >= 0 && ptmp.second + access[1][i] < M && visited[ptmp.first + access[0][i]][ptmp.second + access[1][i]] < 0)
			{
				visited[ptmp.first + access[0][i]][ptmp.second + access[1][i]] = cur + 1;
				q.push({ ptmp.first + access[0][i], ptmp.second + access[1][i] });
			}
		}
	}
	printf("%d", answer);
	return 0;
}
