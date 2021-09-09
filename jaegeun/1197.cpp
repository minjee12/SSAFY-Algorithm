// 최소 스패닝 트리
// https://www.acmicpc.net/problem/1197

#include <iostream>
#include <queue>
#include <vector>

#define MAX_VERTEX 10001
#define MAX_EDGE 100001

using namespace std;

int V = 0, E = 0;

int parent[MAX_VERTEX];

int find_root(int member)
{
	if (parent[member] == 0) return member;
	return parent[member] = find_root(parent[member]);
}

bool setUnion(int a, int b)
{
	int root_a = find_root(a);
	int root_b = find_root(b);
	if (root_a == root_b) return false;
	parent[root_b] = root_a;
	return true;
}

// 비교 함수 재정의
struct compair
{
	bool operator() (pair<int, pair<int, int>> b, pair<int, pair<int, int>>f)
	{
		return b.first > f.first;
	}
};

int main()
{
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, compair> pq;
	cin >> V >> E;

	for (int i = 0; i < E; i++)
	{
		int A, B, C; cin >> A >> B >> C;
		pq.push({ C, {A, B } });
	}

	int e_cnt = 0, w_cnt = 0;
	int pq_size = pq.size();
	for (int i = 0; i < pq_size; i++)
	{
		if (e_cnt == V - 1) break;
		int w = pq.top().first;
		int v1 = pq.top().second.first;
		int v2 = pq.top().second.second;

		if (setUnion(v1, v2))
		{
			e_cnt++;
			w_cnt += w;
		}
		pq.pop();
	}
	cout << w_cnt << '\n';
	return 0;
}