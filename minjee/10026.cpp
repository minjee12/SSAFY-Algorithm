// B 66, G 71, R 82
#include<iostream>
#include<queue>
using namespace std;

int N;
int cntY = 0; // 적록색약
int cntN = 0; // 아닌사람
char arr[100][100];
bool cY[100][100]; // 적록색약
bool cN[100][100]; // 아닌사람
typedef struct {
	int y, x;
} Dir;

Dir d[4] = { {0,1},{0,-1},{1,0},{-1,0} };

void bfsN(int y, int x) { //적록색약은 방문, 아닌사람은 방문하지 않은 경우
	queue<Dir> q;
	q.push({ y,x });
	cN[y][x] = true;
	while (!q.empty()) {
		Dir s = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nyN = s.y + d[i].y;
			int nxN = s.x + d[i].x;
			int diffN = abs(arr[nyN][nxN] - arr[s.y][s.x]);
			if (diffN == 0 && !cN[nyN][nxN] && nyN >= 0 && nxN >= 0 && nyN < N && nxN < N) {
				q.push({ nyN, nxN });
				cN[nyN][nxN] = true;
			}

		}

	}
}

void bfs(int y, int x) { //적록색약, 아닌사람 모두 방문하지 않은 경우
	queue<Dir> qY, qN;
	qY.push({ y,x });
	qN.push({ y,x });
	cY[y][x] = true;
	cN[y][x] = true;
	while (!qN.empty()) {  // 적록색약, 아닌사람 모두 탐색 후 방문체크
		Dir sY = qY.front();
		Dir sN = qN.front();
		qY.pop();
		qN.pop();
		for (int i = 0; i < 4; i++) {
			int nyY = sY.y + d[i].y;
			int nxY = sY.x + d[i].x;
			int nyN = sN.y + d[i].y;
			int nxN = sN.x + d[i].x;
			int diffY = abs(arr[nyY][nxY] - arr[sY.y][sY.x]);
			int diffN = abs(arr[nyN][nxN] - arr[sN.y][sN.x]);
			if (diffN == 0 && !cN[nyN][nxN] && nyN >= 0 && nxN >= 0 && nyN < N && nxN < N) {
				qN.push({ nyN, nxN });
				cN[nyN][nxN] = true;
			}
			if ((diffY == 0 || diffY == 11) && !cY[nyY][nxY] && nyY >= 0 && nxY >= 0 && nyY < N && nxY < N) {
				qY.push({ nyY, nxY });
				cY[nyY][nxY] = true;
				
			}
			
		}
		
	}
	while (!qY.empty()) {  //적록색약인 사람이 방문할 수 있는 나머지 공간 탐색 후, 방문 체크
		Dir sY = qY.front();
		qY.pop();
		for (int i = 0; i < 4; i++) {
			int nyY = sY.y + d[i].y;
			int nxY = sY.x + d[i].x;
			int diffY = abs(arr[nyY][nxY] - arr[sY.y][sY.x]);
			if ((diffY == 0 || diffY == 11) && !cY[nyY][nxY] && nyY >= 0 && nxY >= 0 && nyY < N && nxY < N) {
				qY.push({ nyY, nxY });
				cY[nyY][nxY] = true;

			}
			
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!cN[i][j]) {
				if (!cY[i][j]) {
					cntY++;
					bfs(i, j);
				}
				else {
					bfsN(i, j);
				}
				cntN++;
			}
		}
	}
	cout << cntN << " " << cntY;
	return 0;
}