#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//위 아래 왼 오 (1,2,3,4)

int N, M, K;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

struct Node {
	int num;
	int dir;
	int visited;
};

struct Past {
	int num;
	int k;
};

int start_dir[401] = {};
vector<int> ord_dir[401][4];
vector<Node> map[21][21];
Past smell[21][21] = {};
int ans = -1;

int isInside(int y, int x) {
	if (y < 0 || y >= N || x < 0 || x >= N) return 0;
	return 1;
}

void set_smell() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j].empty()) continue;
			smell[i][j].num = map[i][j].front().num;
			smell[i][j].k = K;
		}
	}
}

int can_move(int y, int x) {

	if (!isInside(y, x) || (smell[y][x].num!=0)) return 0;

	return 1;
}

int find_my_smell(int y, int x, int num) {
	if (isInside(y, x) && smell[y][x].num == num) return 1;
	return 0;
}

void move_shark() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x].empty()) continue;

			int sz = map[y][x].size();

			for (int k = 0; k < sz; k++) {
				if (map[y][x][k].visited == 1) continue;

				int d = map[y][x][k].dir;
				int n = map[y][x][k].num;
				//map[y][x][k].visited = -1;
				int chk = 0;

				for (int z = 0; z < 4; z++) {
					int nd = ord_dir[n][d][z];

					int ny = y + dir[nd][0];
					int nx = x + dir[nd][1];

					if (can_move(ny, nx)) {
						chk = 1;
						map[ny][nx].push_back({ n,nd,1 });
						break;
					}
				}
				if (!chk) {//못 들어갔으면 자기 번호 자리 찾기
					for (int z = 0; z < 4; z++) {
						int nd = ord_dir[n][d][z];

						int ny = y + dir[nd][0];
						int nx = x + dir[nd][1];

						if (find_my_smell(ny, nx, n)) {
							map[ny][nx].push_back({ n,nd,1 });
							break;
						}
					}
				}
			}
			vector<Node> temp;
			for (int k = 0; k < sz; k++) {
				if (map[y][x][k].visited == 1)
					temp.push_back({ map[y][x][k].num,map[y][x][k].dir,1 });
			}
			map[y][x].clear();

			int t_sz = temp.size();

			for (int k = 0; k < t_sz; k++) {
				map[y][x].push_back({ temp[k].num,temp[k].dir,1 });
			}
			temp.clear();
		}
	}
}

int cmp(Node front, Node back) {
	return front.num < back.num;
}

void remove_shark() {

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x].empty()) continue;

			if (map[y][x].size() == 1) {
				map[y][x][0].visited = 0;
				continue;
			}
			
			sort(map[y][x].begin(), map[y][x].end(), cmp);

			while (map[y][x].size() != 1) {
				map[y][x].pop_back();
			}
			map[y][x][0].visited = 0;
		}
	}

}

void refresh_smell() {

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if(smell[y][x].k > 0){
				smell[y][x].k -= 1;
				if (smell[y][x].k == 0) smell[y][x].num = 0;
			}
		}
	}
}

int count_shark() {

	int ret = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x].empty()) continue;
			ret++;
		}
	}

	return ret;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int x;
			cin >> x;
			if (x == 0) continue;
			map[i][j].push_back({ x,0,0 });
		}
	}

	for (int i = 1; i <= M; i++) {
		int d;
		cin >> d;
		start_dir[i] = d - 1;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!map[i][j].empty()) {
				map[i][j].front().dir = start_dir[map[i][j].front().num];
			}
		}
	}

	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				int d;
				cin >> d;
				ord_dir[i][j].push_back(d - 1);
			}
		}
	}

	int tick = 0;
	for (int i = 1; i <= 1000; i++) {
		//냄새 남기기
		set_smell();

		//상어 이동하기
		move_shark();
		
		//냄새 갱신
		refresh_smell();
		
		//격자로 쫓아내기
		remove_shark();
		
		//상어 세기
		int cnt = count_shark();

		if (cnt == 1) {
			ans = i;
			break;
		}
	}

	cout << ans << "\n";

	return 0;
}