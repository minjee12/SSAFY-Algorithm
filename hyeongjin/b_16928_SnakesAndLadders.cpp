#include<stdc++.h>
using namespace std;
int vmap[101], step[101];
void play(int a)
{
	int cur;
	queue<int> q;
	q.push(a);
	while (!q.empty())
	{
		cur = q.front();
		q.pop();
		if (cur == 100)
		{
			printf("%d", step[100]);
			return;
		}
		for (int i = 1; i < 7; ++i) {
			if (cur+i < 101 && ((step[cur + i] > (step[cur] + 1)) || step[cur + i] == 0))
			{
				step[cur + i] = step[cur] + 1;
				if (vmap[cur + i] != cur + i)
				{
					if (step[vmap[cur + i]] > step[cur + i] || step[vmap[cur + i]] == 0)
					{
						step[vmap[cur + i]] = step[cur + i];
						q.push(vmap[cur + i]);
					}
				}
				else
					q.push(cur + i);
			}
		}
	}

}
int main()
{
	for (int i = 0; i < 101; ++i)
		vmap[i] = i;
	int N, M, tmp1, tmp2;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N+M; ++i)
	{
		scanf("%d %d", &tmp1, &tmp2);
		vmap[tmp1] = tmp2;
	}
	play(1);

	return 0;
}
