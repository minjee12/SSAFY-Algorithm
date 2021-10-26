// 소가 길을 건너간 이유 3
// https://www.acmicpc.net/problem/14469

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int N; cin >> N;

	vector<pair<int, int>> cows(N);

	for (int i = 0; i < N; i++) {
		cin >> cows[i].first >> cows[i].second;
	}
	sort(cows.begin(), cows.end());

	int total_time = 0;
	for (int i = 0; i < N; i++) {
		if (total_time < cows[i].first) total_time += (cows[i].first - total_time + cows[i].second);
		else total_time += cows[i].second;
	}
	cout << total_time;
	return 0;

}