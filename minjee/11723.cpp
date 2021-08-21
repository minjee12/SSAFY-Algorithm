#include<iostream>
#include<string>
#include<cmath>
using namespace std;

int bit = 0;
long long int M;
int N;
string str;
void add(int x) {
	bit = bit | (1 << (x - 1));
}

void remove(int x) {
	bit = bit & ~(1 << (x - 1));
}

bool check(int x) {
	return bit & (1 << (x - 1));
}

void toggle(int x) {
	bit = bit ^ (1 << (x - 1));
}

void all() {
	bit = pow(2, 20) - 1;
}

void empty() {
	bit = 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> str;
		if (str == "add") {
			cin >> N;
			add(N);
		}
		else if (str == "remove") {
			cin >> N;
			remove(N);
		}
		else if (str == "check") {
			cin >> N;
			cout << int(check(N)) << "\n";
		}
		else if (str == "toggle") {
			cin >> N;
			toggle(N);
		}
		else if (str == "all") all();
		else if (str == "empty") empty();
	}
	return 0;
}