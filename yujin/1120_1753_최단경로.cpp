#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int v, e, start;
int d[20001];
vector<pair<int, int>> node[20001];

int main(void)
{
	//input
	cin >> v >> e >> start;
	for (int i = 0; i < e; i++)
	{
		int a = 0, b = 0, c = 0; 
		cin >> a >> b >> c;
		node[a].push_back({ b, c });
	}
	for (int i = 1; i <= v; i++) {
		d[i] = 21e8;
	}

	priority_queue<pair<int, int>> pq;
	pq.push({ 0, start });
	d[start] = 0;

	while (pq.empty() == 0)
	{
		int cost = -pq.top().first;
		int now = pq.top().second;
		pq.pop();

		for (int i = 0; i < node[now].size(); i++)
		{
			int next = node[now][i].first;
			int next_cost = node[now][i].second;

			if (d[next] > cost + next_cost)
			{
				d[next] = cost + next_cost;
				pq.push(make_pair(-d[next], next));
			}
		}
	}

	//output
	for (int i = 1; i <= v; i++)
	{
		if (d[i] == 21e8) cout << "INF" << "\n";
		else cout << d[i] << "\n";
	}

	return 0;
}