#include<stdc++.h>
using namespace std;

int N, L, R;
int arr[50][50];

int ax[2] = { 0,1 };
int ay[2] = { 1,0 };
int main()
{
	ios::sync_with_stdio(false);
	memset(arr, -1, sizeof(arr));
	vector<set<int> > a;
	int date = 0, tmp, flag = 0, ftmp =0;
	set<int> stmp;
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			scanf("%d", &arr[i][j]);
		}
	}
	while (1)
	{
		a.clear();
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				for (int k = 0; k < 2; ++k)
				{
					if (i + ax[k] < N && j + ay[k] < N)
					{
						tmp = abs(arr[i][j] - arr[i + ax[k]][j + ay[k]]);
						if (tmp >= L && tmp <= R)
						{
							flag = 0;
							ftmp = 0;
							if (a.size() == 0) {
								stmp.clear();
								stmp.insert(i*N+j);
								stmp.insert( (i + ax[k])*N + j + ay[k]);
								a.push_back(stmp);
								flag = 1;
							}
							for (int t = 0; t < a.size(); ++t)	 
							{
								if (a[t].count(i * N + j) == 1 && a[t].count((i + ax[k]) * N + j + ay[k]) == 1) {
									flag = 1;
									break;
								}
								else if (a[t].count(i * N + j) || a[t].count((i + ax[k]) * N + j + ay[k]))
								{
									a[t].insert(i * N + j);
									a[t].insert((i + ax[k]) * N + j + ay[k]);
									flag = 2;
									ftmp = t;
									break;
								}
							}
							if (flag == 0)
							{
								stmp.clear();
								stmp.insert(i * N + j);
								stmp.insert((i + ax[k]) * N + j + ay[k]);
								a.push_back(stmp);
							}
							else if (flag == 2)	 // union-join
							{
								for (int t = ftmp + 1; t < a.size(); ++t)
								{
									if (a[t].count(i * N + j) || a[t].count((i + ax[k]) * N + j + ay[k]))
									{
										a[ftmp].insert(a[t].begin(), a[t].end());
										a[t].clear();
										break;
									}
								}
							}
						}

					}
				}



			}
		}

		if (a.empty() || date > 2000)
			break;
		for (int i = 0; i < a.size(); ++i)
		{
			if (a[i].size() == 0)
				continue;
			tmp = 0;
			for (auto iter = a[i].begin(); iter != a[i].end(); iter++)
			{
				tmp += arr[(*iter)/N][(*iter)%N];
			}
			tmp = tmp / a[i].size();
			for (auto iter = a[i].begin(); iter != a[i].end(); iter++)
			{
				arr[(*iter)/N][(*iter)% N] = tmp;
			}
		}
		date++;
	}
	printf("%d", date);
	return 0;

}
