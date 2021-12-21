#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
#define MAX 10001

int N, M;
unordered_map<string, int> hs;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int ans = 0;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		hs[str] = 1;
	}

	for (int i = 0; i < M; i++) {
		string str;
		cin >> str;

		if (hs[str] == 1) ans++;
	}

	cout << ans << "\n";
	return 0;
}