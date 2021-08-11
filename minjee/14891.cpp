#include<iostream>
#include<cstring>
using namespace std;

char w[5][9];
int K;
bool used[5];

void rotate(int wheel, int NS) {
	if (used[wheel] == true || wheel < 1 || wheel > 4) return;

	char left = w[wheel][6];   //left,right는 return후 값이 돌아오지 않음 => 초기화 필요
	char right = w[wheel][2];

	if (NS == 1) {
		for (int i = 7; i >= 0; i--) {
			w[wheel][i + 1] = w[wheel][i];
		}
		w[wheel][0] = w[wheel][8];
		used[wheel] = true;
		if (w[wheel + 1][6] != right) {
			rotate(wheel + 1, -1);
			right = w[wheel][2];
		}
		if (w[wheel - 1][2] != left) {
			rotate(wheel - 1, -1);
			left = w[wheel][6];
		}
	}

	else if (NS == -1) {
		w[wheel][8] = w[wheel][0];
		for (int i = 1; i < 8; i++) {
			w[wheel][i - 1] = w[wheel][i];
		}
		w[wheel][7] = w[wheel][8];
		used[wheel] = true;
		if (w[wheel + 1][6] != right) {
			rotate(wheel + 1, 1);
			right = w[wheel][2];
		}
		if (w[wheel - 1][2] != left) {
			rotate(wheel - 1, 1);
			left = w[wheel][6];
		}
	}

}

int main() {
	int sum = 0;
	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> w[i][j];
		}
	}
	
	cin >> K;
	for (int i = 0; i < K; i++) {
		memset(used, false, sizeof(used));
		int wheel, NS;
		cin >> wheel >> NS;
		rotate(wheel, NS);
	}

	if (w[1][0] == '1') sum += 1;
	if (w[2][0] == '1') sum += 2;
	if (w[3][0] == '1') sum += 4;
	if (w[4][0] == '1') sum += 8;
	cout << sum;
	return 0;
}