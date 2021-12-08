#include <string>
#include <iostream>
using namespace std;

int N, M;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string orig;
	int ans = 0;

	cin >> N >> M;

	cin >> orig;
	
	for (int i = 0; i < M; i++) {
		int k = 0;
		if (orig[i] == 'O') continue;
		else {
			while (orig[i + 1] == 'O' && orig[i + 2] == 'I') {
				k++;
				i += 2;
				if (k == N) {
					k--;
					ans++;
				}
			}
		}
	}

	cout << ans << "\n";

	return 0;
}