#include<iostream>
using namespace std;

int h, w;
char arr[102][102];
int ret[102][102];
bool check[102];

void func() {

	for (int i = 1; i <= h; i++) {
		if (arr[i][1] == 'c') {
			ret[i][1] = 0;
			check[i] = true;
		}
		else {
			ret[i][1] = -1;
			check[i] = false;
		}
	}

	for (int i = 1; i <= h; i++) {
		for (int j = 2; j <= w; j++) {
			if (arr[i][j] == 'c') {
				ret[i][j] = 0;
				check[i] = true;
			}
			else if (arr[i][j] == '.' && check[i] == true) {
				ret[i][j] = ret[i][j - 1] + 1;
			}
			else if (arr[i][j] == '.' && check[i] == false) {
				ret[i][j] = -1;
			}
		}
	}
}

int main() {
	cin >> h >> w;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> arr[i][j];
		}
	}
	func();
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cout << ret[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}