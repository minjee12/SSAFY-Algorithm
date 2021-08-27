// 여러분의 다리가 되어 드리겠습니다!
// https://www.acmicpc.net/problem/17352

#include <iostream>

int parent[300001];
int level[300001];

using namespace std;

int find_root(int member)
{
	if (parent[member]==0) return member;
	return parent[member] = find_root(parent[member]);
}

void setUnion(int a, int b)
{
	int root_a = find_root(a);
	int root_b = find_root(b);
	if (level[root_a] < level[root_b]) swap(root_a, root_b);
	level[root_a] += level[root_b];
	parent[root_b] = root_a;
}

int main()
{
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int N = 0; cin >> N;
	for (int i = 1; i <= N; i++) level[i] = i;
	for (int i = 0; i < N - 2; i++)
	{
		int island1, island2; cin >> island1 >> island2;
		setUnion(island1, island2);
	}

	for (int i = 1; i <= N; i++)
		if (parent[i] == 0) cout << i << " ";
		
	return 0;
}