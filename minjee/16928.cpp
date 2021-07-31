#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int arr[102]; // ��ٸ� or �� �̵� ��ġ
bool c[102]; // ��ٸ� or �� üũ
bool check[102]; // bfs üũ
int cnt[102]; // �ֻ��� Ƚ��

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
			int y = x + i;    //x�� ����Ȱ� y�� ����
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
		arr[p] = q; // ��ٸ� ����(from p, to q)
		c[p] = true; // ��ٸ� ���� üũ(���߿� Ƚ�� ī��Ʈ�Ҷ� �ߺ� ī��Ʈ �ǹǷ� 1�� ����)
	}

	for (int y = 0; y < m; y++) {
		int u, v;
		cin >> u >> v;
		arr[u] = v;// �� ����
		c[u] = true;// �� ���� üũ(���߿� Ƚ�� ī��Ʈ�Ҷ� �ߺ� ī��Ʈ �ǹǷ� 1�� ����)

	}
	bfs(1);
	cout << cnt[100];

	return 0;
}

