#include <iostream>
#include <memory.h>
using namespace std;
#define MAX 101

int N, L;
int map[MAX][MAX] = {};
int used[MAX][MAX] = {};
int ans = 0;

void col_chk() {

	for (int x = 0; x < N; x++) {
		int prev_num = map[0][x];
		int dat[10] = {};
		memset(used, 0, sizeof(used));
		int cant = 0;
		dat[prev_num] = 1;
		for (int y = 1; y < N; y++) {
			//col 체크
			prev_num = map[y - 1][x];

			if (map[y][x] == prev_num && used[y-1][x] == 0) {
				dat[prev_num]++;
				continue;
			}
			else if (map[y][x] == prev_num - 1) {  
				//전 층보다 한 층 낮다면
				int chk = 0;
				for (int i = y; i < y + L; i++) {
					if (map[i][x] == map[y][x] && used[i][x]==0)
						chk++;
					else break;
				}
				if (chk >= L) {
					for (int i = y; i < y + L; i++) {
						used[i][x] = 1;
					}
				}
				else {
					cant = 1;
					break;
				}
				dat[map[y][x]] = 0;
			}
			else if (map[y][x] == prev_num + 1) {
				//전 층보다 한 단계 높다면
				if (dat[prev_num] >= L) {
					dat[prev_num] = 0;
					continue;
				}
				else {
					int chk = 0;
					for (int i = y - L; i < y; i++) {
						if (used[i][x] == 0 && map[i][x] == prev_num)
							chk++;
						else break;
					}
					if (chk >= L) {
						for (int i = y - L; i < y; i++) {
							used[i][x] = 1;
						}
					}
					else {
						cant = 1;
						break;
					}
				}
			}
			else if(map[y][x] > prev_num + 1 || map[y][x] < prev_num-1){
				cant = 1;
				break;
			}
		}
		if (!cant) ans++;
	}
}

void row_chk() {

	for (int y = 0; y < N; y++) {
		int prev_num = map[y][0];
		int dat[10] = {};
		memset(used, 0, sizeof(used));
		int cant = 0;
		dat[prev_num] = 1;
		for (int x = 1; x < N; x++) {
			//col 체크
			prev_num = map[y][x - 1];

			if (map[y][x] == prev_num && used[y][x-1]==0) {
				dat[prev_num]++;
				continue;
			}
			else if (map[y][x] == prev_num - 1) {
				//전 층보다 한 층 낮다면
				int chk = 0;
				for (int i = x; i < x + L; i++) {
					if (map[y][i] == map[y][x] && used[y][i] == 0)
						chk++;
					else break;
				}
				if (chk >= L) {
					for (int i = x; i < x + L; i++) {
						used[y][i] = 1;
					}
				}
				else {
					cant = 1;
					break;
				}
				dat[map[y][x]] = 0;
			}
			else if (map[y][x] == prev_num + 1) {
				//전 층보다 한 단계 높다면
				if (dat[prev_num] >= L) {
					dat[prev_num] = 0;
					continue;
				}
				else {
					int chk = 0;
					for (int i = x - L; i < x; i++) {
						if (used[y][i] == 0 && map[y][i] == prev_num)
							chk++;
						else break;
					}
					if (chk >= L) {
						for (int i = x - L; i < x; i++) {
							used[y][i] = 1;
						}
					}
					else {
						cant = 1;
						break;
					}
				}
			}
			else if(map[y][x] > prev_num + 1 || map[y][x] < prev_num - 1){
				cant = 1;
				break;
			}
		}
		if (!cant) ans++;
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> L;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}

	//한줄씩만 체크하면 됨

	row_chk();

	col_chk();

	cout << ans << "\n";

	return 0;
}