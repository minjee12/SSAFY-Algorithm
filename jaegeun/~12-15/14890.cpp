// 경사로
// https://www.acmicpc.net/problem/14890

#define MAX 100

#include <iostream>
#include <cstring>

using namespace std;

int N, L;
int cnt = 0;
int board[MAX][MAX];
int temp[MAX][MAX];

bool check_row(int idx) {
    int base = board[idx][0];
    bool is_ramp[MAX] = { false };
    for (int i = 1; i < N; i++) {
        if (board[idx][i] == base) {
            continue;
        }
        //if (board[idx][i] == board[idx][i - 1]) continue;
        if (board[idx][i] - board[idx][i - 1] == -1) // 내려감
        {
            for (int j = 0; j < L; j++) {
                if (board[idx][i + j] != board[idx][i]) return false; // 경사로 기준 높이와 다름
                is_ramp[i + j] = true;
            }
            base = board[idx][i];
            i += (L - 1);
            continue;
        }
        else if (board[idx][i] - board[idx][i - 1] == 1) // 올라감
        {
            for (int j = 0; j < L; j++) {
                if (i - 1 - j < 0) return false; // 범위 초과로 경사로를 놓을 수 없음
                if (board[idx][i - 1 - j] != board[idx][i - 1]) return false; // 경사로 기준 높이와 다름
                if (is_ramp[i - 1 - j]) return false; // 이미 경사로 놓임
                is_ramp[i - 1 - j] = true;
            }
            base = board[idx][i];
            continue;
        }
        else return false;
    }
    return true;
}

void rotate_board() {
    memcpy(temp, board, sizeof(board));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = temp[j][N - 1 - i];
        }
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        bool result = check_row(i);
        if (result) {
            cnt++;
        }
    }
    rotate_board();
    for (int i = 0; i < N; i++) {
        bool result = check_row(i);
        if (result) {
            cnt++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen_s(new FILE*, "text.txt", "r", stdin);

    cin >> N >> L;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    solve();
    cout << cnt;
    return 0;
}