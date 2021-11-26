#include <iostream>
#include <queue>
#include <memory.h>
#include <vector>
using namespace std;

int N, M;
const int m = 999999999;
//편의점, 집
struct Node {
	int tar;
	int cost;
};

bool operator<(Node back, Node front) {
	return front.cost < back.cost;
}

priority_queue<Node> pq;
int house[5001] = {};
int market[5001] = {};
vector<Node> vec[5001];
int used[5001] = {};
int result[5001] = {};
int min_dist = 999999999;
int ans = 999999999;
void init() {
	for (int i = 1; i <= N; i++) result[i] = m;
	memset(used, 0, sizeof(used));
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		vec[a].push_back({ b,c });
		vec[b].push_back({ a,c });
	}

	int p, q;

	cin >> p >> q;

	for (int i = 0; i < p; i++) {
		cin >> house[i];
	}

	for (int i = 0; i < q; i++) {
		cin >> market[i];
	}

	for (int i = 0; i < q; i++) {
		pq.push({ market[i],0 });
		init();
		used[0] = 1;

		while (!pq.empty()) {
			Node cur = pq.top();
			pq.pop();

			if (used[cur.tar] != 0) continue;
			int flag = 0;
			for (int j = 0; j < p; j++) {
				if (cur.tar == house[j]) {
					flag = 1;
					break;
				}
			}
			if (flag) break;
			used[cur.tar] = 0;

			int n = vec[cur.tar].size();

			for (int j = 0; j < n; j++) {
				Node next = vec[cur.tar][j];

				if (result[next.tar] > cur.cost + next.cost) {
					result[next.tar] = cur.cost + next.cost;
					pq.push({ next.tar,result[next.tar] });
				}
			}
		}

		for (int j = 0; j < p; j++) {
			if (min_dist > result[house[j]]) {
				min_dist = result[house[j]];
				ans = house[j];
			}
		}
	}
	cout << ans << endl;

	return 0;
}