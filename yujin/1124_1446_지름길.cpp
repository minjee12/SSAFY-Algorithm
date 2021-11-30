#include <iostream>
#include <vector>
using namespace std;

struct info {
	int e;
	int d;
};

info tmp;
int dist[10001]; //dist[i] : i��ġ���� �ּҰ�
vector<info> v[10001];

int main() {
	int n, d, start, end, dis;
	cin >> n >> d;
	for (int i = 0; i < n; i++) {
		cin >> start >> end >> dis;
		if (end - start <= dis) continue; //���� ���̺��� �������� �� �� ���
		if (end > d) continue; // ��ǥ�ϴ� ��ġ���� �� ū ���(�������� �Ұ��ϹǷ�)
		v[start].push_back({end, dis});
	}

	for (int i = 1; i <= d; i++) {
		dist[i] = i;
	}

	int prev = 0;
	for (int i = 0; i <= d; i++) {
		if (i == 0) prev = -1;
		else prev = dist[i - 1];
		dist[i] = min(dist[i], prev + 1);

		//i ��ġ�� �������� ������
		for (int j = 0; j < v[i].size(); j++) {
			int nd = v[i][j].d;
			int ne = v[i][j].e;

			//if (ne > d) continue;
			if (dist[i] + nd < dist[ne]) {
				dist[ne] = dist[i] + nd;
			}
		}
	}
	cout << dist[d];
	return 0;
}