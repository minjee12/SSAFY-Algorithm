// 회의실 배정
// https://www.acmicpc.net/problem/1931

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(pair<int,int> f, pair<int,int> b)
{
	if (f.second < b.second) return true;
	if (f.second > b.second) return false;
	return f.first < b.first;
}
int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int n; cin >> n;
	vector<pair<int, int>> vect(n);
	for (int i = 0; i < n; i++)
	{
		int st, ed; cin >> st >> ed;
		vect[i] = { st, ed };
	}
	sort(vect.begin(), vect.end(), comp);

	int cnt = 0;
	int end_t = 0;
	for (int i = 0; i < n; i++)
	{
		if (end_t <= vect[i].first)
		{
			cnt++;
			end_t = vect[i].second;
		}
	}
	cout << cnt << '\n';
	return 0;
}