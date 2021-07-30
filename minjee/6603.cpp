#include<iostream>
#include<cstring>
using namespace std;

int k;
int s[6];  //b

void lotto(int m[12], int a, int b) {
	if (b == 6) {
		for (int i = 0; i < 6; i++) {
			cout << s[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = a; i < k; i++) {
		s[b] = m[i];
		lotto(m, i + 1, b + 1);
	}
}

int main() {
	int arr[12];  //a
	while(true) {
		cin >> k;
		if (k == 0) break;
		for (int i = 0; i < k; i++) {
			cin >> arr[i];
		}

		lotto(arr, 0, 0);
		memset(arr, 0, sizeof(arr));
		cout << "\n";

	}
	return 0;
}