// 완전 범죄
// https://www.acmicpc.net/problem/13700

#define MAX 100001

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int N, S, D, K;
int d[2] = { 0, };
bool police[MAX];
bool visited[MAX];

int solve() {
    queue<pair<int, int>> q;
    q.push({ S, 0 });
    visited[S] = true;
    while (q.size()) {
        int cx = q.front().first;
        int cs = q.front().second;

        q.pop();
        for (int i = 0; i < 2; i++) {
            int nx = cx + d[i];
            if (nx < 1 || nx > N) continue;
            if (police[nx]) continue;
            if (visited[nx]) continue;
            if (nx == D) return cs + 1;
            visited[nx] = true;
            q.push({ nx, cs + 1 });
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen_s(new FILE*, "text.txt", "r", stdin);
    cin >> N >> S >> D >> d[0] >> d[1] >> K;
    d[1] = 0 - d[1];
    for (int i = 0; i < K; i++) {
        int n; cin >> n;
        police[n] = true;
    }
    if (S == D) {
        cout << 0;
        return 0;
    }
    int result = solve();
    if (result == -1) cout << "BUG FOUND";
    else cout << result;
    return 0;
}
