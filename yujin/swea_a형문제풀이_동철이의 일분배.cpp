/*

#include <stdio.h>
#include <string.h>
int n;
int p[20][20];
int visited[20];
double answer;

void dfs(int dep, double sum) {
	//backtracking
	if (sum * 100 <= answer) return;

	if (dep == n+1) {
		if (sum * 100 > answer) answer = sum * 100;
		return;
	}

	for (int j = 1; j <= n; j++) {
		if (visited[j] == 1) continue;
		visited[j] = 1;
		dfs(dep + 1, sum * p[dep][j] * 0.01);
		visited[j] = 0;
	}
}

int main() {

	int test_case = 0;
	scanf("%d", &test_case);
	for (int t = 1; t <= test_case; t++) {
		scanf("%d", &n);
		memset(p, 0, sizeof(p));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &p[i][j]);
			}
		}

		answer = 0;
		dfs(1, 1);

		printf("#%d %.6lf\n", t, answer);
	}
	
	return 0;
}

*/