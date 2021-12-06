#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct info {
	int x;
	int y;
	int num;
};

bool operator<(info back, info front) {
	return front.num < back.num;
}

int n, k;
int S, X, Y;
priority_queue<info> q;
int map[201][201];
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

int main() {

	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int val = 0;
			cin >> val;
			map[i][j] = val;
			q.push({ i, j, val });
		}
	}
	cin >> S >> X >> Y;

	//s초동안
	for (int i = 1; i <= S; i++) {
		queue<info> tmp;

		//숫자가 작은거부터 증식
		while(!q.empty()) {
			int xx = q.top().x;
			int yy = q.top().y;
			int nn = q.top().num;
			q.pop();

			for (int l = 0; l < 4; l++) {
				int nx = xx + dx[l];
				int ny = yy + dy[l];

				if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
				if (map[nx][ny] > 0) continue;
				map[nx][ny] = nn;
				tmp.push({ nx, ny, nn });
			}
		}

		while (!tmp.empty()) {
			q.push({ tmp.front().x, tmp.front().y, tmp.front().num });
			tmp.pop();
		}

	}

	cout << map[X][Y] << "\n";

	return 0;
}