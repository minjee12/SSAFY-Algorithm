// B 66, G 71, R 82
#include<iostream>
#include<queue>
using namespace std;

int N;
int cntY = 0; // ���ϻ���
int cntN = 0; // �ƴѻ��
char arr[100][100];
bool cY[100][100]; // ���ϻ���
bool cN[100][100]; // �ƴѻ��
typedef struct {
	int y, x;
} Dir;

Dir d[4] = { {0,1},{0,-1},{1,0},{-1,0} };

void bfsN(int y, int x) { //���ϻ����� �湮, �ƴѻ���� �湮���� ���� ���
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

void bfs(int y, int x) { //���ϻ���, �ƴѻ�� ��� �湮���� ���� ���
	queue<Dir> qY, qN;
	qY.push({ y,x });
	qN.push({ y,x });
	cY[y][x] = true;
	cN[y][x] = true;
	while (!qN.empty()) {  // ���ϻ���, �ƴѻ�� ��� Ž�� �� �湮üũ
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
	while (!qY.empty()) {  //���ϻ����� ����� �湮�� �� �ִ� ������ ���� Ž�� ��, �湮 üũ
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