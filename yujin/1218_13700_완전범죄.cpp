#include <iostream>
#include <queue>
using namespace std;

int police[50001];
int visited[100001];
int n, s, d, f, b, k;
queue<pair<int, int> > q; //������ġ, ��ưȽ��

bool check_police(int now) {
	for (int i = 0; i < k; i++) {
		if (police[i] == now) return false; //�������ΰ���
	}
	return true;
}

int bfs() {
	q.push({ s, 0 });
	visited[s] = 1;

	while (!q.empty()) {
		int now = q.front().first;
		int cnt = q.front().second;
		q.pop();

		//���� ��ġ�� �뵵�� ���̸�
		if (now == d) return cnt;
		
		//������ ���� ���
		int nnow = now + f;
		//�̵��� ��ġ�� �������� continue
		if (check_police(nnow)) {
			if (0 < nnow && nnow <= 100000) {
				if (visited[nnow] != 1) {
					visited[nnow] = 1;
					q.push({ nnow, cnt + 1 });
				}
			}
		}
		
		//�ڷ� ���� ���
		nnow = now - b;
		//�̵��� ��ġ�� �������� continue
		if (check_police(nnow)) {
			if (0 < nnow && nnow <= 100000) {
				if (visited[nnow] != 1) {
					visited[nnow] = 1;
					q.push({ nnow, cnt + 1 });
				}
			}
		}
	}

	return -1;
}

int main() {

	cin >> n >> s >> d >> f >> b >> k;
	for (int i = 0; i < k; i++) {
		cin >> police[i];
	}

	int res = bfs();
	if (res == -1) cout << "BUG FOUND\n";
	else cout << res << "\n";

	return 0;
}