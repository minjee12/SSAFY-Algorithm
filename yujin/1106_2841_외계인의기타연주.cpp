#include <iostream>
#include <vector>
using namespace std;

vector<int> guitar[7];
int n, p;
int cnt;

void play(int line, int fret) {
	while (1) {
		if (guitar[line].empty()) {
			guitar[line].push_back(fret);
			cnt++;
			return;
		}
		if (guitar[line].back() == fret) break;
		else if (guitar[line].back() > fret) {
			guitar[line].pop_back();
			cnt++;
		}
		else {
			guitar[line].push_back(fret);
			cnt++;
		}
	}
}

int main() {
	cin >> n >> p;
	for (int i = 0; i < n; i++) {
		int line = 0;
		int fret = 0;
		cin >> line >> fret;
		play(line, fret);
	}

	cout << cnt << "\n";
	return 0;
}