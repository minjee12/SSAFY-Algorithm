#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct info {
	int y;
	int x;
	int size;
	int dir; //1상, 2하, 3좌, 4우
	int state; //1live, 0dead
};

bool comp(info front, info back) {
	return front.size > back.size;
}

int n, m, k;
vector<info> map;
int cnt[101][101];

int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,-1,1 };

void go() {
	for (int i = 0; i < map.size(); i++) {
		if (map[i].state == 0) continue;
		int y = map[i].y;
		int x = map[i].x;
		int s = map[i].size;
		int d = map[i].dir;

		int ny = y + dy[d];
		int nx = x + dx[d];
		
		//약품에 도착한 셀 미생물 절반 죽고, 이동방향 반대, 0인 미생물 없앰
		if (ny == 0 || nx == 0 || ny == n - 1 || nx == n - 1) {
			s = s / 2;
			if (d == 1) d = 2;
			else if (d == 2) d = 1;
			else if (d == 3) d = 4;
			else if (d == 4) d = 3;
		}

		cnt[y][x]--;
		if (s == 0) {
			map[i].state = 0;
		}
		else {
			map[i].y = ny;
			map[i].x = nx;
			map[i].size = s;
			map[i].dir = d;
			cnt[ny][nx]++;
		}
	}
}

void combine() {
	sort(map.begin(), map.end(), comp);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (cnt[i][j] >= 2) {
				int total_size = 0;
				int idx = 0;
				int first = 0;
				for (int z = 0; z < map.size(); z++) {
					if (map[z].y == i && map[z].x == j && map[z].state == 1) {
						total_size += map[z].size;
						if (first == 0) {
							first++;
							idx = z;
						}
						else {
							map[z].state = 0;
						}
					}
				}
				map[idx].size = total_size;
				cnt[i][j] = 1;
			}
		}
	}
}

int main() {
	int test_case = 0;
	cin >> test_case;

	for (int t = 1; t <= test_case; t++) {
		//init
		map.clear();
		memset(cnt, 0, sizeof(cnt));

		//input
		cin >> n >> m >> k;
		for (int i = 0; i < k; i++) {
			int y, x, s, d;
			cin >> y >> x >> s >> d;
			map.push_back({ y, x, s, d, 1 });
			cnt[y][x]++;
		}

		for (int i = 1; i <= m; i++) {
			//다음방향 셀로 이동
			go();

			//두개 이상 군집 합치기
			combine();
		}

		//output
		int res = 0;
		for (int i = 0; i < map.size(); i++){
			if (map[i].state == 0) continue;
			res += map[i].size;
		}
		cout << "#" << t << " " << res << "\n";
	}

	return 0;
}