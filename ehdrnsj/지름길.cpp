#include <iostream>
#include <algorithm>
using namespace std;

int N, D;

struct node {
	int start, end;
	int dist;
};

bool compare(node front, node back) {
	return front.start < back.start;
}

node road[15];

int mini = 21e8;

void bt(int now, int total_dist) {
	if (now == D) {
		mini = (total_dist < mini) ? total_dist : mini;
		return;
	}

	for (int i = 0; i <= N; i++) {
		if (road[i].start < now) continue;
		int next = (road[i].start - now) + road[i].dist;
		bt(road[i].end, total_dist + next);
	}
}

int main() {
	cin >> N >> D;

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		int s, e, d;
		cin >> s >> e >> d;
		if (e - s <= d || e > D) continue;
		road[cnt++] = { s, e, d };
	}
	N = cnt;
	road[N] = { D, D, 0 };

	sort(road, road + N, compare);

	bt(0, 0);

	cout << mini;

	return 0;
}