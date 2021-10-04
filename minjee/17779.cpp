// 게리맨더링2
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int N;
int A[20][20];
bool arr[20][20]; // 5 구역 찾기
int mini = 100000;
int sum[5];
typedef struct {
	int y, x;
} Dir;

Dir s[4];

void result() {
	sort(sum, sum+5);
	mini = min(mini, sum[4] - sum[0]);
}

void count() {
	for (int i = 0; i < s[0].y; i++) {
		for (int j = 0; j <= s[0].x; j++) sum[0] += A[i][j];
		for (int j = s[0].x + 1; j < N; j++) sum[1] += A[i][j];
	}
	for (int i = s[3].y + 1; i < N; i++) {
		for (int j = 0; j < s[3].x; j++) sum[2] += A[i][j];
		for (int j = s[3].x; j < N; j++) sum[3] += A[i][j];
	}
	for (int j = 0; j < s[1].x; j++) {
		for (int i = s[0].y; i < s[1].y; i++) sum[0] += A[i][j];
		for (int i = s[1].y; i <= s[3].y; i++) sum[2] += A[i][j];
	}
	for (int j = s[2].x + 1; j < N; j++) {
		for (int i = s[0].y; i <= s[2].y; i++) sum[1] += A[i][j];
		for (int i = s[2].y + 1; i <= s[3].y; i++) sum[3] += A[i][j];
	}

	int a = s[0].x - s[1].x;
	int b = s[3].x - s[1].x;
	int c = 0;
	int d = 0;
	for (int i = s[0].y; i < s[1].y; i++) {
		for (int j = s[1].x; j < s[1].x + a; j++) {
			sum[0] += A[i][j];
			arr[i][j] = true;
		}
		a--;
	}
	for (int i = s[0].y; i < s[2].y; i++) {
		for (int j = s[2].x; j > s[2].x - b; j--) {
			sum[1] += A[i][j];
			arr[i][j] = true;
		}
		b--;
	}
	for (int i = s[1].y + 1; i <= s[3].y; i++) {
		for (int j = s[1].x; j <= s[1].x + c; j++) {
			sum[2] += A[i][j];
			arr[i][j] = true;
		}
		c++;
	}
	for (int i = s[2].y + 1; i <= s[3].y; i++) {
		for (int j = s[2].x; j >= s[2].x - d; j--) {
			sum[3] += A[i][j];
			arr[i][j] = true;
		}
		d++;
	}
	for (int i = s[0].y; i <= s[3].y; i++) {
		for (int j = s[1].x; j <= s[2].x; j++) {
			if (arr[i][j] == false) sum[4] += A[i][j];
		}
	}
}

void caseD(int y, int x) {
	s[0] = { y,x };
	for (int d1 = 1; d1 <= x; d1++) {
		if (y + d1 == N - 1 || x - d1 < 0) return;
		for (int d2 = 1; d2 < N - y - d1; d2++) {
			if (y + d2 == N-1 || x + d2 == N) break;
			s[1] = { y + d1, x - d1 };
			s[2] = { y + d2, x + d2 };
			s[3] = { y + d1 + d2, x - d1 + d2 };
			count();
			result();
			memset(arr, false, sizeof(arr));
			memset(sum, false, sizeof(sum));
		}
	}
}

void caseXY() {
	for (int i = 0; i < N - 2; i++) {
		for (int j = 1; j < N - 1; j++) {
			caseD(i, j);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}

	caseXY();

	cout << mini;
	return 0;
}