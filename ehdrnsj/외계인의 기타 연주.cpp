#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int N, P;
vector<stack<int>> guitar(7);
int melody_joongbok;
int cnt;

void pret_pop(int rope, int melody) {
	while (!guitar[rope].empty()) {
		int melody_now = guitar[rope].top();

		if (melody_now < melody) return;
		else if (melody_now == melody) {
			melody_joongbok = 1;
			return;
		}
		cnt++;
		guitar[rope].pop();
	}
}

void play(int rope, int melody) {
	if (guitar[rope].empty()) {
		cnt++;
		guitar[rope].push(melody);
		return;
	}

	int melody_high = guitar[rope].top();
	melody_joongbok = 0;
	if (melody_high > melody) {
		cnt++;
		guitar[rope].pop();
		pret_pop(rope, melody);
	}
	else if (melody_high == melody) {
		melody_joongbok = 1;
	}

	if (!melody_joongbok) {
		cnt++;
		guitar[rope].push(melody);
	}
}

int main() {
	cin >> N >> P;

	for (int i = 0; i < N; i++) {
		int rope, melody;
		cin >> rope >> melody;
		play(rope, melody);
	}
	cout << cnt;

	return 0;
}