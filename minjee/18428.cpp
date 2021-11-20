#include<iostream>
#include<vector>
using namespace std;

typedef struct {
	int y, x;
} Dir;

vector<Dir> t;
vector<Dir> v;
char arr[6][6];
int N;
Dir d[4] = { {1,0},{0,1},{-1,0},{0,-1} };
bool flag = false;

void check() {
	for (int i = 0; i < t.size(); i++) {
		for (int j = 0; j < 4; j++) {
			int y = t[i].y;
			int x = t[i].x;
			while (true) {
				y += d[j].y;
				x += d[j].x;
				if (x < 0 || x >= N || y < 0 || y >= N || arr[y][x] == 'O') break;
				if (arr[y][x] == 'S') return;
			}
		}
	}
	flag = true;
	return;
}

void dfs(int x, int cnt) {
	if (cnt == 3) {
		check();
		return;
	}
	for (int i = x; i < v.size(); i++) {
		int dy = v[i].y;
		int dx = v[i].x;
		arr[dy][dx] = 'O';
		dfs(i + 1, cnt + 1);
		arr[dy][dx] = 'X';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 'T') t.push_back({ i,j });
			else if (arr[i][j] == 'X') v.push_back({ i,j });
		}
	}
	dfs(0,0);
	if (flag == true) cout << "YES";
	else cout << "NO";
	
	return 0;
}