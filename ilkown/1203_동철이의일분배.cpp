#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
double map[17][17] = {};
double maxPer = -999999999;
double ans = 0;
int used[17] = {};

vector<double> percent;
void findMax(int lev , double ans) {

	if (ans <= maxPer) return;

	if (lev == N) {

		if (maxPer < ans)
			maxPer = ans;
		return;
	}

	for (int i = 1; i <= N; i++) {
		if (used[i] != 0) continue;
		if (map[lev + 1][i] == 0) continue;
		used[i] = 1;
		if (lev == 0)
			findMax(lev + 1, map[lev + 1][i] * 0.01);
		else
			findMax(lev + 1, ans * map[lev + 1][i] * 0.01);
		used[i] = 0;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int tc;
	cin >> tc;

	int k = 1;

	while (tc--) {

		cin >> N;



		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> map[i][j];
			}
		}

		maxPer = -999999999;

		findMax(0,0);

		cout.precision(6);
		
		cout << fixed;
		cout << "#" << k++ << " " << maxPer * 100 << "\n";
	}

	

	return 0;
}
