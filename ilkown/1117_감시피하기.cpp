#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
	int y,  x;
};

int N;
char map[7][7] = {};
int visited[7][7] = {};
vector<Node> student;
vector<Node> teacher;
string ans;

int isInside(int y, int x) {
	if (y<0 || y>N || x<0 || x>N) return 0;

	return 1;
}

int cant_see() {

	int can = 0;
	int cant = 0;
	int st_sz = student.size();
	int t_sz = teacher.size();


	for (int i = 0; i < t_sz; i++) {
		int ty = teacher[i].y;
		int tx = teacher[i].x;
		for (int j = 0; j < st_sz; j++) {
			int y = student[j].y;
			int x = student[j].x;

			if (ty == y) {
				if (tx - x > 0) {//y축은 같고 teacher가 오른쪽에 있을 때
					int nx = x + 1;

					if (!isInside(y, nx)) continue;

					while (1) {
						if (!isInside(y, nx)) break;
						if (map[y][nx] == 'T') {
							cant++;
							break;
						}
						if (map[y][nx] == 'O') {
							can++;
							break;
						}
						nx += 1;
					}
				}
				else if(tx - x < 0){
					int nx = x - 1;

					if (!isInside(y, nx)) continue;

					while (1) {
						if (!isInside(y, nx)) break;
						if (map[y][nx] == 'T') {
							cant++;
							break;
						}
						if (map[y][nx] == 'O') {
							can++;
							break;
						}
						nx -= 1;
					}
				}
			}
			if (tx == x) {
				if (ty - y > 0) {//teacher가 밑에 있을 때

					int ny = y + 1;

					if (!isInside(ny, x)) continue;

					while (1) {
						if (!isInside(ny, x)) break;
						if (map[ny][x] == 'T') {
							cant++;
							break;
						}
						if (map[ny][x] == 'O') {
							can++;
							break;
						}
						ny++;
					}
				}
				else if (ty - y < 0) {
					int ny = y - 1;

					if (!isInside(ny, x)) continue;

					while (1) {
						if (!isInside(ny, x)) break;
						if (map[ny][x] == 'T') {
							cant++;
							break;
						}
						if (map[ny][x] == 'O') {
							can++;
							break;
						}
						ny--;
					}
				}
			}
		}
	}

	if (cant >= 1) return -1;
	else return 1;
}

void set_wall(int lev) {

	if (lev == 3) {

		int chk = cant_see();

		if (chk == 1) ans = "YES";

		return;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j] == 1 || map[i][j] != 'X') continue;

			visited[i][j] = 1;
			map[i][j] = 'O';
			set_wall(lev + 1);
			map[i][j] = 'X';
			visited[i][j] = 0;
		}
	}

}


int main() {

	cin >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'T') teacher.push_back({ i,j });
			if (map[i][j] == 'S') student.push_back({ i,j });
		}
	}

	set_wall(0);

	if (ans == "") cout << "NO" << endl;
	else cout << ans << endl;

	return 0;
}