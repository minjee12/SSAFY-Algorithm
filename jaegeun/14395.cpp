// 4연산
// https://www.acmicpc.net/problem/14395

#include <iostream>
#include <queue>

#define LL unsigned long long
using namespace std;

void bfs(LL s, LL t)
{
	queue<pair<LL, string>> q;
	bool minus = false, div = false;
	q.push({ s, "" });

	while (q.size())
	{
		LL val = q.front().first;
		string cmd = q.front().second;
		q.pop();
		if (val == t)
		{
			cout << cmd << "\n";
			exit(0);
		}
		if (val * val <= t && val * val > 1) q.push({ val * val, cmd + "*" });
		if (val * 2 <= t && val + val > 0) q.push({ val + val, cmd + "+" });
		if (!minus)
		{
			q.push({ 0, cmd + "-" });
			minus = true;
		}
		if (!div)
		{
			q.push({ 1, cmd + "/" });
			div = true;
		}
	}
}

int main()
{
	LL s, t; cin >> s >> t;
	if (s == t) {
		cout << 0 << '\n';
		return 0;
	}
	bfs(s, t);
	cout << "-1" << "\n";
	return 0;
}