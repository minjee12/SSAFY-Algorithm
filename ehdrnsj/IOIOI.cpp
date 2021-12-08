#include <iostream>

#define MAX 1000001

using namespace std;

int N, M;
char S[MAX];
int IOI_list[MAX];
int IOI_idx;

void IOI_count() {
	int IOI_cnt = 0;

	for (int i = 0; i < M - 2; i++) {
		if (S[i] == 'I' && S[i + 1] == 'O' && S[i + 2] == 'I') {
			IOI_cnt++;
			i++;
			continue;
		}
		if (IOI_cnt != 0) {
			IOI_list[IOI_idx++] = IOI_cnt;
			IOI_cnt = 0;
		}
	}
	if (IOI_cnt != 0) {
		IOI_list[IOI_idx++] = IOI_cnt;
	}
}

int IOI_print() {
	int cnt = 0;
	for (int i = 0; i < IOI_idx; i++) {
		if (IOI_list[i] < N) continue;
		cnt += IOI_list[i] - N + 1;
	}
	return cnt;
}

int main() {
	cin >> N >> M;
	cin >> S;

	IOI_count();
	cout << IOI_print();

	return 0;
}