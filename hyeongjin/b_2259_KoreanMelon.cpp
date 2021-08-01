#include<stdc++.h>
using namespace std;
vector<vector<int> > inarr(6, vector<int>(2, 0));
int N;

int main()
{
	scanf("%d", &N);
	int tmp, tmp2, last = -1, mx = 0, my = 0, ax = 0,ay = 0,flag =0;
	for(int i = 0; i < 6 ; ++i)
	{
		scanf("%d %d", &tmp, &tmp2);
		inarr[i][0] = tmp;
		inarr[i][1] = tmp2;
		if (inarr[i][0] < 3 && inarr[i][1] > ax)
			ax = inarr[i][1];
		if (inarr[i][0] > 2 && inarr[i][1] > ay)
			ay = inarr[i][1];
	}
	for (int i = 0; i < 6; ++i)
	{
		if (inarr[i][0] == inarr[(i + 2) % 6][0] && inarr[(i + 1) % 6][0] == inarr[(i + 3) % 6][0])
		{
			mx = inarr[(i + 1) % 6][1];
			my = inarr[(i + 2) % 6][1];
		}
	}

	printf("%d", (ax * ay - mx * my ) *N);
	return 0;
}
