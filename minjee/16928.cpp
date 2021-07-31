#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int arr[102]; // 사다리 or 뱀 이동 위치
bool c[102]; // 사다리 or 뱀 체크
bool check[102]; // bfs 체크
int cnt[102]; // 주사위 횟수

void bfs(int start) {
	cnt[1] = 0;
	queue<int> q;
	q.push(start);
	check[start] = 1;
	while (!q.empty()) {
		/*for (auto x : cnt)
			cout << x;
		cout << endl;*/
		int x = q.front();
		q.pop();
		for (int i = 1; i <= 6; i++) {
			int y = x + i;    //x와 연결된것 y에 저장
			if (y > 100) return;
			if (c[y]) {
				check[y] = 1;
				y = arr[y];
			}
			if (!check[y]) {
				q.push(y);
				check[y] = 1;
				cnt[y] = cnt[x] + 1;
			}
			
		}

	}

}

int main() {
	int n, m;
	cin >> n >> m;
	for (int y = 0; y < n; y++) {
		int p, q;
		cin >> p >> q;
		arr[p] = q; // 사다리 간선(from p, to q)
		c[p] = true; // 사다리 여부 체크(나중에 횟수 카운트할때 중복 카운트 되므로 1씩 빼줌)
	}

	for (int y = 0; y < m; y++) {
		int u, v;
		cin >> u >> v;
		arr[u] = v;// 뱀 간선
		c[u] = true;// 뱀 여부 체크(나중에 횟수 카운트할때 중복 카운트 되므로 1씩 빼줌)

	}
	bfs(1);
	cout << cnt[100];

	return 0;
}

