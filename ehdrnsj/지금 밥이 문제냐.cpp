#include <iostream>
#include <string.h>
using namespace std;

char ipv8[100];
unsigned long long deci;

void jegop(unsigned long long num, int cnt) {
	for (int i = 0; i < cnt * 8; i++) num *= 2;
	deci += num;
}

void ip2deci() {
	deci = 0;
	int cnt = 8;
	for (char* pstr = strtok(ipv8, "."); pstr != NULL; pstr = strtok(NULL, ".")) {
		cnt--;
		char tmp[20];
		strcpy(tmp, pstr);
		jegop(atoi(tmp), cnt);
	}
	cout << deci << "\n";
}

void jegopgun(int cnt) {
	unsigned long long num = 1;
	for (int i = 0; i < cnt * 8; i++) num *= 2;
	int n = deci / num;
	deci %= num;
	cout << n;
	if (cnt != 0) cout << ".";
}

void deci2ip() {
	for (int cnt = 7; cnt >= 0; cnt--) {
		jegopgun(cnt);
	}
	cout << "\n";
	//deci = 0;
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int type;
		cin >> type;

		if (type == 1) {
			cin >> ipv8;
			ip2deci();
		}
		else if (type == 2) {
			cin >> deci;
			deci2ip();
		}
	}

	return 0;
}