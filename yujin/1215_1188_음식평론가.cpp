#include <iostream>
using namespace std;

int GCD(int a, int b){
	if (a%b == 0) return b;
	return GCD(b, a%b);
}

int main(void)
{
	int N, M;
	cin >> N >> M;
	cout << M - GCD(N, M) << "\n";
	return 0;
}