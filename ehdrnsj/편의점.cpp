#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>

#define INF 10000000
using namespace std;

struct node {
	int n;
	int dist;
};

int n, m;
vector<node> alist[100001];
int d[5001];

int p, q;
int check_house[5001], check_store[5001];
int arr_house[5001], arr_store[5001];

int mini = 21e8;
int idx_mini;

bool operator<(node back, node front) {
	return front.dist < back.dist;
}

void dijkstra(int start) {
	priority_queue<node> pq;
	fill(d, d + 5001, INF);

	pq.push({ start, 0 });
	d[start] = 0;

	while (!pq.empty()) {
		node now = pq.top();
		pq.pop();

		if (now.n != start && check_house[now.n] == 1) continue;
		if (now.dist > d[now.n]) continue;

		int size = alist[now.n].size();
		for (int i = 0; i < size; i++) {
			node next = alist[now.n][i];
			if (check_house[next.n]) continue;
			if (d[next.n] > now.dist + next.dist) {
				d[next.n] = now.dist + next.dist;
				if (d[next.n] == 1) return;
				pq.push({ next.n, d[next.n] });
			}
		}
	}
}

void input() {
	//노드 연결
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		alist[a].push_back({ b, c });
		alist[b].push_back({ a, c });
	}
	//집 목록
	cin >> p >> q;
	for (int i = 1; i <= p; i++) {
		int n;
		cin >> n;
		check_house[n] = 1;
		arr_house[i] = n;
	}	
	sort(arr_house + 1, arr_house + p + 1);
	//편의점 목록
	for (int i = 1; i <= q; i++) {
		int n;
		cin >> n;
		arr_store[i] = n;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	input();
	//집마다 편의점 최단거리 구하기
	for (int i = 1; i <= p; i++) {
		//해당집의 편의점까지 최단거리
		dijkstra(arr_house[i]);
		//편의점까지 적힌 거리를 비교(최소값 찾기)
		for (int j = 1; j <= q; j++) {
			if (d[arr_store[j]] < mini) {
				mini = d[arr_store[j]];
				idx_mini = arr_house[i];
				if (mini == 1) goto EXIT;
			}
		}
	}

EXIT:
	cout << idx_mini;

	return 0;
}