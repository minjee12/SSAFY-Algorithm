#include <vector>
#include <iostream>
using namespace std;

int M, S;

int f_dir[8][2] = { {0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1} };
int s_dir[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };

struct Node {
	int d, visited;
};
vector<Node> fish[5][5];
vector<int> egg[5][5];
int dead[5][5] = {};
int move_shark[64][3]= {};

int map[5][5] = {};

int isInside(int y, int x) {
	if(y < 1 || y > 4 || x < 1 || x > 4)
		return 0;
	return 1;
}

int sz = 0;
vector<int> temp;
void comb(int lev) {
	if(lev == 3) {
		for (int i = 0; i < lev; i++) {
			move_shark[sz][i] = temp[i];
		}
		sz++;
		return;
	}

	for (int i = 0; i < 4; i++) {
		temp.push_back(i);
		comb(lev + 1);
		temp.pop_back();
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M >> S;

	comb(0);

	for (int i = 0; i < M; i++) {
		int fx, fy, d;
		cin >> fy >> fx >> d;
		fish[fy][fx].push_back({ d-1,0 });
	}
	int sx, sy;
	cin >> sy >> sx;

	map[sy][sx] = 2;

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			dead[i][j] = -1;
		}
	}
	
	for(int cur = 1; cur<=S;cur++){
		//알 낳기
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				if (map[i][j] == 2) {
					sy = i;
					sx = j;
				}
				if (!fish[i][j].empty()) {
					int n = fish[i][j].size();
					for (int k = 0; k < n; k++) {
						egg[i][j].push_back(fish[i][j][k].d);
					}
				}
			}
		}

		//물고기 움직이기
		for (int y = 1; y <= 4; y++) {
			for (int x = 1; x <= 4; x++) {
				if (!fish[y][x].empty()) {
					int n = fish[y][x].size();

					int change = 0;
					for (int k = 0; k < n; k++) {
						if (fish[y][x][k].visited == 1) continue;
						change = 1;
						int d = fish[y][x][k].d;

						int ny = y + f_dir[d][0];
						int nx = x + f_dir[d][1];
						int cant = 0;

						int prev_d = d;

						while (!isInside(ny, nx) || dead[ny][nx]!= -1 || map[ny][nx]==2) {
							d -= 1;
							if (d < 0) d = 7;

							ny = y + f_dir[d][0];
							nx = x + f_dir[d][1];
							if (d == prev_d) {
								cant = 1;
								break;
							}
						}
						if(cant==0)
							fish[ny][nx].push_back({ d,1 });
						else {
							fish[y][x][k].visited = 1;
						}
					}
					
					if (change) {
						vector<int> sv;
						for (int k = 0; k < n; k++) {
							if (fish[y][x][k].visited == 1) sv.push_back(fish[y][x][k].d);
						}
						fish[y][x].clear();

						n = sv.size();
						if (n == 0) continue;
						for (int k = 0; k < n; k++) {
							fish[y][x].push_back({ sv[k],1 });
						}
					}
				}
			}
		}

		//상어 차례
		int max_ = 0;
		int shark_y = 0;
		int shark_x = 0;
		int tp[5][5] = {};
		int eat[5][5] = {};

		for (int i = 0; i < 64; i++) {
			int food = 0;
			int ny = sy;
			int nx = sx;
			memset(tp, 0, sizeof(tp));

			for (int j = 0; j < 3; j++) {
				ny += s_dir[move_shark[i][j]][0];
				nx += s_dir[move_shark[i][j]][1];

				if(!isInside(ny, nx)) break;
				
				if(!fish[ny][nx].empty() && !tp[ny][nx]) {
					food += fish[ny][nx].size();
					tp[ny][nx] += fish[ny][nx].size();
				}
			}
			if(max_ < food && isInside(ny,nx)) {
				shark_y = ny;
				shark_x = nx;
				memcpy(eat, tp, sizeof(tp));
				max_ = food;
			}
		}

		if (max_ == 0) {
			for (int i = 0; i < 64; i++) {
				shark_y = sy;
				shark_x = sx;
				for (int j = 0; j < 3; j++) {
					shark_y += s_dir[move_shark[i][j]][0];
					shark_x += s_dir[move_shark[i][j]][1];
					if (!isInside(shark_y, shark_x)) break;
				}
				if (isInside(shark_y, shark_x)) break;
			}
		}

		map[sy][sx] = 0;
		map[shark_y][shark_x] = 2;

	
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				if (eat[i][j] > 0) {
					dead[i][j] = cur;
					fish[i][j].clear();
				}
			}
		}

		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				if (dead[i][j] == -1) continue;

				if (cur - dead[i][j] == 2) {
					dead[i][j] = -1;
				}
			}
		}

		//알 부화 시키기
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				if (!fish[i][j].empty()) {
					int n = fish[i][j].size();
					for (int k = 0; k < n; k++) {
						fish[i][j][k].visited = 0;
					}
				}
				if (!egg[i][j].empty()) {
					int n = egg[i][j].size();
					for (int k = 0; k < n; k++) {
						fish[i][j].push_back({ egg[i][j][k],0 });
					}
					egg[i][j].clear();
				}
			}
		}

	}

	int ans = 0;

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (fish[i][j].empty()) continue;
			ans += fish[i][j].size();
		}
	}
	cout << ans << endl;
	return 0;
}
