#include <iostream>
using namespace std;

int N, M;
int city[201][201] = {};
int plan[1001] = {};
int visited[201] = {};

void dfs(int a) {
	visited[a] = 1;

	for (int i = 1; i <= N; i++) {
		if (city[a][i] == 1 && visited[i] == 0)
			dfs(i);
	}
}

int main() {

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> city[i][j];
		}
	}
	for (int i = 1; i <= M; i++) {
		cin >> plan[i];
	}

	dfs(plan[1]);
	int flag = 0;
	for (int i = 1; i <= M; i++) {
		if (visited[plan[i]] == 0) {
			flag = 1;
			break;
		}
	}

	if (flag) cout << "NO" << endl;
	else cout << "YES" << endl;

	
	return 0;
}