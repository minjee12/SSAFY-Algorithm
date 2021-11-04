#include <iostream>
#include <string>
#include <cmath>
#include <string.h>
#include <vector>
using namespace std;

typedef unsigned long long ull;

string ulltobin(ull a) {
	string temp = "";
	string bin = "";

	while (a / 2 != 0) {
		temp += a % 2 + '0';
		a /= 2;
	}
	temp += a+'0';
	if (temp.length() < 64) {
		while (temp.length() != 64) temp += "0";
	}
	int k = 0;
	for (int i = temp.length() - 1; i >= 0; i--) {
		bin += temp[i];
	}

	return bin;
}

string intTobin(int a) {
	string temp = "";
	string bin = "";

	while (a / 2 != 0) {
		temp += a % 2 + '0';
		a /= 2;
	}
	temp += a + '0';
	if (temp.length() < 8)
		while (temp.length() != 8) temp += "0";
	int k = 0;
	for (int i = temp.length() - 1; i >= 0; i--) {
		bin += temp[i];
	}

	return bin;
}

int binTodec(string bin) {
	int k = bin.length() - 1;
	int dec = 0;
	int n = bin.length();

	for (int i = 0; i < n; i++) {
		dec += ((bin[i] - '0') * pow(2, k));
		k--;
	}

	return dec;
}


string binToip(string bin) {

	string ip = "";
	string bit_8 = "";
	int n = bin.length();

	for (int i = 0; i < 64;i+=8) {
		bit_8 = bin.substr(i, 8);
		int dec = binTodec(bit_8);
		ip += to_string(dec) + ".";
	}
	return ip;
}

ull binToull(string bin) {
	int k = bin.length() - 1;
	int n = bin.length();
	ull dec = 0;

	for (int i = 0; i < n; i++) {
		dec += (ull)(bin[i] - '0')*((ull)(pow(2, k--)));
	}

	return dec;
}

ull ipToull(string ip) {

	string bin = "";
	int n = ip.length();
	int idx = 0;

	int a = 0;
	while (1) {
		int cur = ip.find(".", a);
		if (cur == -1) break;

		int dec = atoi(ip.substr(a, cur - a).c_str());
		bin += intTobin(dec);
		a = cur + 1;
	}
	int res = atoi(ip.substr(a, ip.length() - a).c_str());

	bin += intTobin(res);

	if (bin.length() < 63) {
		while (bin.length() != 63) bin += "0";
	}
	ull  ans = binToull(bin);

	return ans;
}

int main() {

	int tc;
	cin >> tc;

	while (tc--) {
		int M;
		string N;	
		char** end = NULL;

		cin >> M >> N;

		if (M == 2) {
			ull a = strtoull(N.c_str(), end, 10);

			string bin = ulltobin(a);
			string ip = binToip(bin);
			ip.pop_back();

			cout << ip << endl;
		}

		else if (M == 1) {
			ull ans = ipToull(N);

			cout << ans << endl;
		}

	}

	return 0;
}