#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n,m;
char arr[10][10];

typedef struct {
	int cam, y, x;
} Dir2;

typedef struct {
	int y, x;
} Dir;

Dir d1[4] = { {1,0},{-1,0},{0,1},{0,-1} };
Dir d2[2][2] = { {{1,0},{-1,0}},{{0,1},{0,-1}} };
Dir d3[4][2] = { {{-1,0},{0,1}}, {{1,0},{0,1}},{{1,0},{0,-1}},{{0,-1},{-1,0}} };
Dir d4[4][3] = { {{-1,0},{0,1},{0,-1}}, {{1,0},{0,1},{-1,0}},{{1,0},{0,-1},{0,1}},{{0,-1},{-1,0},{1,0}} };
Dir d5[4] = { {1,0},{-1,0},{0,1},{0,-1} };

vector<Dir2> v;
vector<vector<Dir2>> run;
vector<Dir2> vv;
bool used[10];

void dd1(int y, int x) {
	int num;
	int maxi = 0;
	for (int i = 0; i < 4; i++) {
		int cnt = 0;
		int ny = y + d1[i].y;
		int nx = x + d1[i].x;
		while (true) {
			if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == '6') break;
			if (arr[ny][nx] == '0') cnt++;
			ny += d1[i].y;
			nx += d1[i].x;
			if (arr[ny][nx] == '1' || arr[ny][nx] == '2' || arr[ny][nx] == '3' || arr[ny][nx] == '4' || arr[ny][nx] == '5' || arr[ny][nx] == '#') {
				ny += d1[i].y;
				nx += d1[i].x;
			}
		}
		
		maxi = max(maxi, cnt);
		if (maxi == cnt) num = i;
	}
	for (int i = 0; i < 1; i++) {
		int ny = y + d1[num].y;
		int nx = x + d1[num].x;
		while (true) {
			if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == '6') break;
			if (arr[ny][nx] == '0') arr[ny][nx] = '#';
			ny += d1[num].y;
			nx += d1[num].x;
			if (arr[ny][nx] == '1' || arr[ny][nx] == '2' || arr[ny][nx] == '3' || arr[ny][nx] == '4' || arr[ny][nx] == '5' || arr[ny][nx] == '#') {
				ny += d1[num].y;
				nx += d1[num].x;
			}
		}
	}
}
void dd2(int y, int x) {
	int num;
	int maxi = 0;
	for (int i = 0; i < 2; i++) {
		int cnt = 0;
		for (int j = 0; j < 2; j++) {
			int ny = y + d2[i][j].y;
			int nx = x + d2[i][j].x;
			while (true) {
				if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == '6') break;
				if (arr[ny][nx] == '0') cnt++;
				ny += d2[i][j].y;
				nx += d2[i][j].x;
				if (arr[ny][nx] == '1' || arr[ny][nx] == '2' || arr[ny][nx] == '3' || arr[ny][nx] == '4' || arr[ny][nx] == '5' || arr[ny][nx] == '#') {
					ny += d2[i][j].y;
					nx += d2[i][j].x;
				}
			}
		}
		maxi = max(maxi, cnt);
		if (maxi == cnt) num = i;
	}
	for (int i = 0; i < 2; i++) {
		int ny = y + d2[num][i].y;
		int nx = x + d2[num][i].x;
		while (true) {
			if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == '6') break;
			if (arr[ny][nx] == '0') arr[ny][nx] = '#';
			ny += d2[num][i].y;
			nx += d2[num][i].x;
			if (arr[ny][nx] == '1' || arr[ny][nx] == '2' || arr[ny][nx] == '3' || arr[ny][nx] == '4' || arr[ny][nx] == '5' || arr[ny][nx] == '#') {
				ny += d2[num][i].y;
				nx += d2[num][i].x;
			}
		}
	}
}
void dd3(int y, int x) {
	int num;
	int maxi = 0;
	for (int i = 0; i < 4; i++) {
		int cnt = 0;
		for (int j = 0; j < 2; j++) {
			int ny = y + d3[i][j].y;
			int nx = x + d3[i][j].x;
			while (true) {
				if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == '6') break;
				if (arr[ny][nx] == '0') cnt++;
				ny += d3[i][j].y;
				nx += d3[i][j].x;
				if (arr[ny][nx] == '1' || arr[ny][nx] == '2' || arr[ny][nx] == '3' || arr[ny][nx] == '4' || arr[ny][nx] == '5' || arr[ny][nx] == '#') {
					ny += d3[i][j].y;
					nx += d3[i][j].x;
				}
			}
		}
		maxi = max(maxi, cnt);
		if (maxi == cnt) num = i;
	}
	for (int i = 0; i < 2; i++) {
		int ny = y + d3[num][i].y;
		int nx = x + d3[num][i].x;
		while (true) {
			if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == '6') break;
			if (arr[ny][nx] == '0') arr[ny][nx] = '#';
			ny += d3[num][i].y;
			nx += d3[num][i].x;
			if (arr[ny][nx] == '1' || arr[ny][nx] == '2' || arr[ny][nx] == '3' || arr[ny][nx] == '4' || arr[ny][nx] == '5' || arr[ny][nx] == '#') {
				ny += d3[num][i].y;
				nx += d3[num][i].x;
			}
		}
	}
}
void dd4(int y, int x) {
	int num;
	int maxi = 0;
	for (int i = 0; i < 4; i++) {
		int cnt = 0;
		for (int j = 0; j < 3; j++) {
			int ny = y + d4[i][j].y;
			int nx = x + d4[i][j].x;
			while (true) {
				if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == '6') break;
				if (arr[ny][nx] == '0') cnt++;
				ny += d4[i][j].y;
				nx += d4[i][j].x;
				if (arr[ny][nx] == '1' || arr[ny][nx] == '2' || arr[ny][nx] == '3' || arr[ny][nx] == '4' || arr[ny][nx] == '5' || arr[ny][nx] == '#') {
					ny += d4[i][j].y;
					nx += d4[i][j].x;
				}
			}
		}
		maxi = max(maxi, cnt);
		if (maxi == cnt) num = i;
	}
	for (int i = 0; i < 3; i++) {
		int ny = y + d4[num][i].y;
		int nx = x + d4[num][i].x;
		while (true) {
			if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == '6') break;
			if (arr[ny][nx] == '0') arr[ny][nx] = '#';
			ny += d4[num][i].y;
			nx += d4[num][i].x;
			if (arr[ny][nx] == '1' || arr[ny][nx] == '2' || arr[ny][nx] == '3' || arr[ny][nx] == '4' || arr[ny][nx] == '5' || arr[ny][nx] == '#') {
				ny += d4[num][i].y;
				nx += d4[num][i].x;
			}
		}
	}
}
void dd5(int y, int x) {
	for (int i = 0; i < 4; i++) {
		int ny = y + d5[i].y;
		int nx = x + d5[i].x;
		while (true) {
			if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == '6') break;
			if (arr[ny][nx] == '0') arr[ny][nx] = '#';
			ny += d5[i].y;
			nx += d5[i].x;
			if (arr[ny][nx] == '1' || arr[ny][nx] == '2' || arr[ny][nx] == '3' || arr[ny][nx] == '4' || arr[ny][nx] == '5' || arr[ny][nx] == '#') {
				ny += d5[i].y;
				nx += d5[i].x;
			}
		}
	}
}

void func(int y, int x) {
	if (arr[y][x] == '1') dd1(y, x);
	else if (arr[y][x] == '2') dd2(y, x);
	else if (arr[y][x] == '3') dd3(y, x);
	else if (arr[y][x] == '4') dd4(y, x);
	else if (arr[y][x] == '5') dd5(y, x);
}

void set(int lev) {
	if (lev == v.size()) {
		run.push_back(vv);
		return;
	}
	for (int i = 0; i < v.size(); i++) {
		if (used[i] == true) continue;
		vv.push_back(v[i]);
		used[i] = true;
		set(lev + 1);
		used[i] = false;
		vv.pop_back();
	}

}

int main() {
	int result = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] != '0' && arr[i][j] != '6' && arr[i][j] != '#') {
				v.push_back({ arr[i][j], i, j });
			}
		}
	}
	set(0);
	int mini = 80;
	for (int k = 0; k < run.size(); k++) {
		for (int i = 0; i < run[k].size(); i++) {
			func(run[k][i].y, run[k][i].x);
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (arr[i][j] == '0') result++;
			}
		}
		mini = min(mini, result);
		result = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (arr[i][j] == '#') arr[i][j] = '0';
			}
		}
	}


	cout << mini << "\n";
	return 0;
}