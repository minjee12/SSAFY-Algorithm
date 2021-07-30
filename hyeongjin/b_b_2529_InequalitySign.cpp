#include<stdc++.h>
using namespace std;
int checked[10], N;
vector<int> order;
char signSet[10];
string lowest, highest;
void hlest(int depth) {
	if (depth == N+1) {
		if (lowest == "")
		{
			for (auto iter = order.begin(); iter != order.end(); iter++)
				lowest += to_string(*iter);
		}
		highest = "";
		for (auto iter = order.begin(); iter != order.end(); iter++)
			highest += to_string(*iter);
		return;
	}
	if (depth > 0)
	{
		if (signSet[depth - 1] == '<')
		{
			for (int i = 0; i < 10; ++i)
			{
				if (checked[i]) continue;
				if (order[depth - 1] < i)
				{
					checked[i] = 1;
					order.push_back(i);
					hlest(depth + 1);
					order.pop_back();
					checked[i] = 0;
				}
			}
		}
		else
		{
			for (int i = 0; i < 10; ++i)
			{
				if (checked[i]) continue;
				if (order[depth - 1] > i)
				{
					checked[i] = 1;
					order.push_back(i);
					hlest(depth + 1);
					order.pop_back();
					checked[i] = 0;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; ++i)
		{
			if (checked[i]) continue;
			checked[i] = 1;
			order.push_back(i);
			hlest(depth + 1);
			order.pop_back();
			checked[i] = 0;
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		scanf(" %c", &signSet[i]);
	}
	hlest(0);
	printf("%s\n%s", highest.c_str(), lowest.c_str());
	return 0;
}
