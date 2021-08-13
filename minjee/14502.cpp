// �� 3�� ��ǥ�� ����: ���
//���̷��� ����: bfs �̿�
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

int N, M;
char arr[9][9];
bool c[9][9]; // bool���� ���������� ������ ���� �ʱⰪ�� false�̴�.
typedef struct {
	int y, x;
} Dir;

Dir d[4] = { {1,0},{0,1},{-1,0},{0,-1} };
vector<Dir> wall; // �ʱ� �ʿ��� 0�� ��ġ ���� -> ���߿��� �� ��ġ 3���� ���� ����
vector<Dir> virus; // �ʱ� �ʿ��� ���̷��� ��ġ
int maxi = 0;

Dir path[3]; // ���� �� ���� 3��
bool used[64]; // 3�� �� ���� ���� ���� used�迭

//�������� ���� �ִ밪 ������Ʈ
void countM() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] == '0' && !c[i][j]) cnt++; //�� ���� 0�ε� bfs�� �湮���� ������ ��������
		}
	}
	maxi = max(maxi, cnt);
}

//path�迭(���� �� ������ ��) �޾Ƽ� bfs ����
void bfs(Dir path[]) {
	queue<Dir> q;
	for (int i = 0; i < 3; i++) {
		int a = path[i].y;
		int b = path[i].x;
		arr[a][b] = '1';   //3���� �� �����
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

void selectWall(int lv) { //���(����)���� ���� �� ���� �� �ִ� ��� ��� üũ
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