#include<stdc++.h>
using namespace std;


int N;
vector<int> checked(55, 0), numberSet(55,0);

void lotto(int dept, int cnt, int from)
{

	if (N - from + cnt < 6 || cnt > 6)
		return;
	if (dept >= 6 && cnt == 6)
	{
		for (int i = 0; i <= N; ++i)
		{
			if (checked[i])
				printf("%d ", numberSet[i]);
		}
		printf("\n");
		return;
	}
	checked[from] = 1;
	lotto(dept + 1, cnt + 1, from + 1);
	checked[from] = 0;
	lotto(dept, cnt, from + 1);
}
int main()
{
	while (1)
	{
		scanf("%d", &N);
		if (!N) break;
		for (int i = 0; i < N; ++i)
		{
			scanf("%d", &numberSet[i]);
		}
		lotto(0,0,0);
		printf("\n");
	}
	return 0;
}
