#include <iostream>
#include <queue>
#include <vector>
#include <string.h> //memset
using namespace std;

struct info {
	int tar;
	int dis;
};

bool operator<(info back, info front) {
	return front.dis < back.dis;
}

int n, m, a, b, c, p, q;
vector<info> v[5001];
vector<int> home;
vector<int> conv;

int res[5001];
int used[5001];
int dis_min = 21e8;
int answer = 0;

int main() {
	
	//input
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		v[a].push_back({ b, c });
		v[b].push_back({ a, c });
	}
	for (int i = 0; i <= n; i++) {
		res[i] = 21e8;
	}
	for (int i = 1; i <= n; i++) res[i] = 21e8;
	cin >> p >> q;
	for (int i = 0; i < p; i++) {
		int x = 0;
		cin >> x;
		home.push_back(x);
	}
	for (int i = 0; i < q; i++) {
		int x = 0;
		cin >> x;
		conv.push_back(x);
	}

	//편의점에서 집까지 거리 갱신
	for (int i = 0; i < conv.size(); i++) {
		//초기화
		memset(used, 0, sizeof(used));
		for (int j = 0; j <= n; j++) {
			res[j] = 21e8;
		}

		priority_queue<info> pq;
		int start = conv[i];
		pq.push({ start, 0 });

		while (!pq.empty()) {
			int t = pq.top().tar;
			int d = pq.top().dis;
			pq.pop();

			if (used[t] == 1) continue;
			used[t] = 1;

			for (int j = 0; j < v[t].size(); j++) {
				int nt = v[t][j].tar;
				int nd = v[t][j].dis;

				if (res[nt] > d + nd) {
					res[nt] = d + nd;
					pq.push({ nt, d + nd });
				}
			}
		}

		for (int j = 0; j < home.size(); j++) {
			if (dis_min > res[home[j]]) {
				dis_min = res[home[j]];
				answer = home[j];
			}
		}
	}

	cout << answer;
	
	return 0;
}