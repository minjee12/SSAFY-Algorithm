// 음식 평론가
// https://www.acmicpc.net/problem/1188

#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int main() {
    freopen_s(new FILE*, "text.txt", "r", stdin);
    int N, M; cin >> N >> M;
    cout << M - gcd(N, M);

    return 0;
}