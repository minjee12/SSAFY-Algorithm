// IOIOI
// https://www.acmicpc.net/problem/5525

#include <iostream>
#include <string>

using namespace std;

int N, M;
string S;
int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N >> M >> S;
	int total_cnt = 0;
	// IOIOIOI의 길이를 구함
	// N의 개수에 따라 개수 계산
	// 다음으로 넘어감
	bool is_ioi = false;
	int o_cnt = 0;
	for (int i = 0; i < S.length(); i++) {
		if (S[i] == 'O' && i + 1 == M) break;
		// IOIOI 시작 조건
		if (S[i] == 'I' && S[i + 1] == 'O' && !is_ioi) { 
			is_ioi = true;
			o_cnt = 0;
		}
		// IOIOI 종료 조건
		if (S[i] == 'O' && is_ioi) {
			if (S[i + 1] == 'O') {
				is_ioi = false;
				if (o_cnt >= N) {
					int ioi_cnt = o_cnt - N + 1;
					total_cnt += ioi_cnt;
				}
			}
		}
		if (S[i] == 'I' && is_ioi && S[i + 1] == 'I') {
			is_ioi = false;
			if (o_cnt >= N) {
				int ioi_cnt = o_cnt - N + 1;
				total_cnt += ioi_cnt;
			}
		}
		if (S[i] == 'O' && is_ioi) o_cnt++;
	}
	if (is_ioi) {
		if (o_cnt >= N) {
			int ioi_cnt = o_cnt - N + 1;
			total_cnt += ioi_cnt;
		}
	}
	cout << total_cnt;
	return 0;
}