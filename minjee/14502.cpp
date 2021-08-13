// 벽 3개 좌표의 조합: 재귀
//바이러스 전파: bfs 이용
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

int N, M;
char arr[9][9];
bool c[9][9]; // bool형은 전역변수로 선언할 때만 초기값이 false이다.
typedef struct {
	int y, x;
} Dir;

Dir d[4] = { {1,0},{0,1},{-1,0},{0,-1} };
vector<Dir> wall; // 초기 맵에서 0인 위치 저장 -> 이중에서 벽 위치 3가지 조합 선택
vector<Dir> virus; // 초기 맵에서 바이러스 위치
int maxi = 0;

Dir path[3]; // 새로 벽 세울 3곳
bool used[64]; // 3개 벽 조합 설정 위한 used배열

//안전영역 개수 최대값 없데이트
void countM() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] == '0' && !c[i][j]) cnt++; //맵 값이 0인데 bfs로 방문하지 않은곳 개수세기
		}
	}
	maxi = max(maxi, cnt);
}

//path배열(새로 벽 지정할 곳) 받아서 bfs 수행
void bfs(Dir path[]) {
	queue<Dir> q;
	for (int i = 0; i < 3; i++) {
		int a = path[i].y;
		int b = path[i].x;
		arr[a][b] = '1';   //3군데 벽 세우기
	}
	for (int i = 0; i < virus.size(); i++) {
		q.push({ virus[i].y, virus[i].x });
		c[virus[i].y][virus[i].x] = true;
	}
	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = y + d[i].y;
			int nx = x + d[i].x;
			if (ny >= 0 && nx >= 0 && ny < N && nx < M && !c[ny][nx] && arr[ny][nx] == '0') {
				q.push({ ny, nx });
				c[ny][nx] = true;
			}
		}
	}
	countM();
}

void selectWall(int lv) { //재귀(조합)으로 새로 벽 세울 수 있는 모든 경우 체크
	if (lv == 3) {
		bfs(path);
		memset(c, false, sizeof(c));
		for (int i = 0; i < 3; i++)
			arr[path[i].y][path[i].x] = '0';

		return;
	}

	for (int i = 0; i < wall.size(); i++) {
		if (used[i] == true) continue;
		if (lv >= 1 && (path[lv - 1].y * M + path[lv - 1].x > wall[i].y * M + wall[i].x)) continue;
		path[lv] = wall[i];
		used[i] = true;
		selectWall(lv + 1);
		used[i] = false;
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == '2') virus.push_back({ i,j });
			else if (arr[i][j] == '0') wall.push_back({ i,j });
		}
	}
	selectWall(0);
	cout << maxi;
	return 0;
}