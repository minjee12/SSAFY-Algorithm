// 이중 우선순위 큐
// https://www.acmicpc.net/problem/7662

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool visited[1000001];

int post()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	int T; cin >> T;
	for (int t = 0; t < T; t++)
	{
		int K; cin >> K;
		priority_queue<pair<int,int>> ascending;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> descending;

		for (int i = 0; i < K; i++)
		{
			char c; int num; cin >> c >> num;
			if (c == 'I')
			{
				ascending.push({ num, i });
				descending.push({ num, i });
				visited[i] = true;
			}
			else
			{
				if (num == 1)
				{
					while (!ascending.empty() && !visited[ascending.top().second])
						ascending.pop();
					if (!ascending.empty())
					{
						visited[ascending.top().second] = false;
						ascending.pop();
					}
				}
				else
				{
					while (!descending.empty() && !visited[descending.top().second])
						descending.pop();
					if (!descending.empty())
					{
						visited[descending.top().second] = false;
						descending.pop();
					}
				}
			}
		}
		while (!ascending.empty() && !visited[ascending.top().second])
			ascending.pop();
		while (!descending.empty() && !visited[descending.top().second])
			descending.pop();
		if (ascending.empty() && descending.empty())
			cout << "EMPTY\n";
		else
			cout << ascending.top().first << " " << descending.top().first << endl;
	}
	return 0;
}