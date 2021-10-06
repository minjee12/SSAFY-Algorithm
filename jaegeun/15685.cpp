// 드래곤 커브
// https://www.acmicpc.net/problem/15685

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 101
using namespace std;

int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

int board[MAX][MAX];

int change_dir(int n)
{
	return (n + 1) % 4;
}

void make_dcurve(int x, int y, int d, int g) {
	vector<int> v_d;
	v_d.push_back(d);
	for (int i = 0; i < g; i++) {
		int size = v_d.size();
		vector<int> v_nd(size);
		std::transform(v_d.rbegin(), v_d.rend(), v_nd.begin(), change_dir);
		v_d.insert(v_d.end(), v_nd.begin(), v_nd.end());
	}

	board[x][y] = true;
	for (int i = 0; i < v_d.size(); i++) {
		int nx = x + dx[v_d[i]];
		int ny = y + dy[v_d[i]];
		board[nx][ny] = true;
		x = nx;
		y = ny;
	}
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int n; cin >> n;
	int x, y, d, g;
	for (int i = 0; i < n; i++) {
		cin >> y >> x >> d >> g;
		make_dcurve(x, y, d, g);
	}
	int cnt = 0;
	for (int i = 0; i < MAX - 1; i++) {
		for (int j = 0; j < MAX - 1; j++) {
			if (board[i][j] && board[i][j + 1] &&
				board[i + 1][j] && board[i + 1][j + 1]) cnt++;
		}
	}
	cout << cnt;
	return 0;
}