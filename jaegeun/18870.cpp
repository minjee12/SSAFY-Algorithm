// 좌표 압축
// https://www.acmicpc.net/problem/18870

#include <iostream>
#include <algorithm>
#include <map>

#define MAX 1000001
using namespace std;

int cord[MAX];

int main()
{
	cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int n; cin >> n;
	map<int, int> m;
	for (int i = 0; i < n; i++)
	{
		cin >> cord[i];
		m.insert({ cord[i], 0 });
	}

	int i = 0;
	for (auto x : m)
	{
		m[x.first] = i++;
	}

	for (int i = 0; i < n; i++)
	{
		auto it = m.find(cord[i]);
		cout << it->second << " ";
	}
	return 0;
}