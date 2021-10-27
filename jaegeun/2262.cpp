// 토너먼트 만들기
// https://www.acmicpc.net/problem/2262

#include <iostream>
#include <cmath>

#define MAX 256

#define logB(x, base) log(x)/log(base)

using namespace std;

int N;
int game_rank[MAX];
void delete_index(int n) {
	for (int i = n; i < N - 1; i++) {
		game_rank[i] = game_rank[i + 1];
	}
	game_rank[N - 1] = 0;
}
int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++) cin >> game_rank[i];
	
	int index_N = 0;
	int total_diff = 0;
	// 가장 랭크 낮은 사람 먼저 떨구기
	while (N != 1) {
		for (int i = 0; i < N; i++) {
			if (game_rank[i] == N) {
				index_N = i;
				break;
			}
		}
		if (index_N == 0) {
			total_diff += game_rank[index_N] - game_rank[index_N + 1];
			delete_index(index_N);
		}
		else if (index_N == N - 1) {
			total_diff += game_rank[index_N] - game_rank[index_N - 1];
			delete_index(index_N);
		}
		else {
			int min_diff = min(game_rank[index_N] - game_rank[index_N - 1],
				game_rank[index_N] - game_rank[index_N + 1]);
			total_diff += min_diff;
			delete_index(index_N);
		}
		
		N--;
	}
	cout << total_diff;
	return 0;
}