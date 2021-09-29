//마법사 상어와 파이어스톰
// pow는 cmath 추가!!
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;

int N, Q;
int arr[65][65];
int L[1000];
int temp[65][65];
bool used[65][65];
int maxi = 0;
int iceSum = 0;
typedef struct {
	int y, x;
} D;

D d[4] = { {-1,0},{1,0},{0,-1},{0,1} };
queue<D> q;
queue<D> m;

void rotate(int y, int x, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp[i][j] = arr[y + size - j - 1][x + i];
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			arr[y + i][x + j] = temp[i][j];
		}
	}
}

void ice_minus(int N) {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] == 0) continue;
			for (int k = 0; k < 4; k++) {
				int y = i + d[k].y;
				int x = j + d[k].x;
				if (arr[y][x] == 0 || y < 0 || x < 0 || y >= N || x >= N) cnt++;
				if (cnt == 2) {
					m.push({ i,j });
					break;
				}
			}
			cnt = 0;
		}
	}
	while (!m.empty()) {
		int yy = m.front().y;
		int xx = m.front().x;
		arr[yy][xx]--;
		m.pop();
	}
}

void ice_sum(int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			iceSum += arr[i][j];
		}
	}
}

//유니온 파인드 사용해보기
void cnt_max(int y, int x, int N) { // bfs
	q.push({ y,x });
	used[y][x] = true;
	int cnt = 1;

	while (!q.empty()) {
		int dy = q.front().y;
		int dx = q.front().x;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = dy + d[i].y;
			int nx = dx + d[i].x;
			if (ny < 0 || nx < 0 || ny >= N || nx >= N || used[ny][nx] == true || arr[ny][nx] == 0) continue;
			q.push({ ny, nx });
			used[ny][nx] = true;
			cnt++;
		}
	}
	maxi = max(maxi, cnt);

}

void run(int N) {
	for (int i = 0; i < Q; i++) {
		int size = pow(2, L[i]);
		int block = N / size; // 부분 격자 개수

		if (size > 1) {
			for (int j = 0; j < block; j++) {
				for (int k = 0; k < block; k++) {
					rotate(j * size, k * size, size);
				}
			}
		}

		ice_minus(N);
	}
	ice_sum(N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (used[i][j] == false && arr[i][j] != 0) cnt_max(i, j, N);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> Q;
	int num = pow(2, N);
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < Q; i++) {
		cin >> L[i];
	}

	run(num);

	cout << iceSum << "\n" << maxi << "\n";
	return 0;
}

// N 범위가 작게 제한 되어있다면, 매번 pow 대신 {1,2,4,8,16,32,64,...} 이런식으로 받아놓고 하면 더 빠름.