#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int arr[9][9];
bool c[10];
typedef struct {
	int y, x;
} Dir;
queue<Dir> zero;
bool flag;

void change(int y, int x) {
	for (int i = 1; i <= 9; i++) {
		if (c[i] == false) {
			arr[y][x] = i;
			return;
		}
	}
}

void func3(int y, int x) { // 정사각형
	int i = (y / 3) * 3;
	int j = (x / 3) * 3;

	for (int k = i; k < i + 3; k++) {
		for (int l = j; l < j + 3; l++) {
			if (arr[k][l] == 0 && (k != y || l != x)) {
				flag = true;
				return;
			}
			c[arr[k][l]] = true;
		}
	}
}

void func2(int y, int x, int yy) { // 세로방향
	if (flag == true || y == 9) return;
	if (arr[y][x] == 0 && (y != yy)) {
		flag = true;
		return;
	}
	c[arr[y][x]] = true;
	func2(y + 1, x, yy);
}

void func1(int y, int x, int xx) { // 가로방향
	if (flag == true || x == 9) return;
	if (arr[y][x] == 0 && (x != xx)) {
		flag = true;
		return;
	}
	c[arr[y][x]] = true;
	func1(y, x + 1, xx);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 0) zero.push({ i,j });
		}
	}
	while (!zero.empty()) {
		memset(c, false, sizeof(c));
		flag = false;
		int y = zero.front().y;
		int x = zero.front().x;
		func1(y, 0, x);

		if (flag) {
			memset(c, false, sizeof(c));
			flag = false;
			func2(0, x, y);
		}
		else {
			change(y, x);
			zero.pop();
			continue;
		}
		if (flag) {
			memset(c, false, sizeof(c));
			flag = false;
			func3(y, x);
		}
		else {
			change(y, x);
			zero.pop();
			continue;
		}
		if (flag) {
			memset(c, false, sizeof(c));
			zero.pop();
			zero.push({ y,x });
		}
		else {
			change(y, x);
			zero.pop();
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}