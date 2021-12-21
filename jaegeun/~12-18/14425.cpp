// 문자열 집합
// https://www.acmicpc.net/problem/14425

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    map<string, int> S;
    for (int i = 0; i < n; i++) {
        string str; cin >> str;
        S[str] = 1;
    }
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        string str; cin >> str;
        if (S[str] == 1) cnt++;
    }
    cout << cnt;
    return 0;
}