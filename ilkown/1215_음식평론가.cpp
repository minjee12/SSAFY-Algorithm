#include <iostream>
using namespace std;

int GCD(int a, int b) {
	if (b == 0) return a;
	return GCD(b, a%b);
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M; //1~100

	cin >> N >> M;

	cout << M - GCD(N, M) << "\n";
	

	return 0;
}