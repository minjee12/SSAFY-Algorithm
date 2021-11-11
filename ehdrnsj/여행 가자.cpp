#include <iostream>

using namespace std;

int N, M;
int arr[201];

int findboss(int member) {
	if (arr[member] == 0) return member;
	int boss = findboss(arr[member]);
	arr[member] = boss;
	return boss;
}

void setUnion(int a, int b) {
	int aboss = findboss(a);
	int bboss = findboss(b);
	if (aboss == bboss) return;
	arr[bboss] = aboss;
}

int main() {
	FILE* f = freopen("ÅØ½ºÆ®.txt", "r", stdin);

	cin >> N >> M;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			int input;
			cin >> input;
			if (input == 1) {
				setUnion(y, x);
			}
		}
	}

	int possible = 1;
	int ex = 0, now = 0;
	for (int y = 1; y <= M; y++) {
		ex = now;
		cin >> now;
		if (y == 1) continue;

		if (findboss(ex) != findboss(now)) {
			possible = 0;
			break;
		}
	}

	if (possible) cout << "YES";
	else cout << "NO";

	return 0;
}