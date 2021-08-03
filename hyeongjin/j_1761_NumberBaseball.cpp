#include<stdc++.h>
using namespace std;

vector<vector<int> > ansSet;
vector<int> order;
vector<int> visited(10);
int answer = 0;
void combi(int d)
{
	if (d == 3) // check strike and ball
	{
		if (order[0] == 3 && order[1] == 2 && order[2] == 4)
		{
			int kkkk = 343;
		}

		int numSep[3],s=0,b=0, all=1;
		vector<int> tmp;
		for (int i = 0; i < ansSet.size(); ++i)
		{
			s = 0;
			b = 0;
			tmp.assign(order.begin(), order.end());
			numSep[0] = ansSet[i][0] / 100;
			numSep[1] = (ansSet[i][0] % 100)/10;
			numSep[2] = ansSet[i][0] % 10;

			for (int j = 0; j < 3; ++j)
			{
				if (tmp[j] == numSep[j])
				{
					s++;
					tmp[j] = 9999;
				}
			}
			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (numSep[j] == tmp[k])
					{
						b++;
						tmp[k] = 9999;
					}
				}
			}
			if (ansSet[i][1] != s || ansSet[i][2] != b)
			{
				all = 0;
				break;
			}
		}
		if (all)
			answer++;
		return;
	}
	for (int i = 1; i < 10; ++i)
	{
		if (visited[i]) continue;
		order.push_back(i);
		visited[i] = 1;
		combi(d + 1);
		order.pop_back();
		visited[i] = 0;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	scanf("%d", &n);
	int num, s, b;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d %d", &num, &s, &b);
		ansSet.push_back({ num,s,b });
	}
	combi(0);
	printf("%d", answer);

	return 0;
}
