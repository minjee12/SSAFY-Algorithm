#include <iostream>
#include <vector>
using namespace std;

struct info {
	int e;
	int d;
};

info tmp;
int dist[10001]; //dist[i] : i위치에서 최소값
vector<info> v[10001];

int main() {
	int n, d, start, end, dis;
	cin >> n >> d;
	for (int i = 0; i < n; i++) {
		cin >> start >> end >> dis;
		if (end - start <= dis) continue; //원래 길이보다 지름길이 더 긴 경우
		if (end > d) continue; // 목표하는 위치보다 더 큰 경우(역주행이 불가하므로)
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

		//i 위치에 지름길이 있으면
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