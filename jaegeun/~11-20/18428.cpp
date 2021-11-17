// 감시 피하기
// https://www.acmicpc.net/problem/18428

#include <iostream>
#include <cstring>
#include <vector>
#define MAX 6

using namespace std;

int N;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
char board[MAX][MAX];

vector<pair<int, int>> pos_T;

void print_board() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}


bool check_pos() {
    for (int t = 0; t < pos_T.size(); t++) {
        // 선생 위치
        int t_x = pos_T[t].first;
        int t_y = pos_T[t].second;

        for (int d = 0; d < 4; d++) {
            int n_x = t_x + dx[d];
            int n_y = t_y + dy[d];
            while (true) {
                if (n_x < 0 || n_x >= N || n_y < 0 || n_y >= N) break;
                if (board[n_x][n_y] == 'O') // 장애물
                {
                    break;
                }
                if (board[n_x][n_y] == 'S') {
                    return false;
                }
                n_x = n_x + dx[d];
                n_y = n_y + dy[d];
            }
        }
    }
    return true;
}

void dfs(int level, int before_x, int before_y) // level : 장애물 개수
{
    if (level == 3) {
        //print_board();
        if (check_pos()) {
            cout << "YES";
            exit(0);
        }
        return;
    }
    char temp_board[MAX][MAX] = { 0, };
    memcpy(temp_board, board, sizeof(board));
    for (int i = before_x; i < N; i++) {
        int j = i > before_x ? 0 : before_y;
        for (j; j < N; j++) {
            if (board[i][j] == 'X') {
                board[i][j] = 'O';
                dfs(level + 1, before_x, before_y + 1);
                memcpy(board, temp_board, sizeof(board));
            }
        }
    }
}

int main()
{
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    freopen_s(new FILE*, "text.txt", "r", stdin);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'T') pos_T.push_back({ i, j });
        }
    }
    dfs(0, 0, 0);

    cout << "NO";
    return 0;
}
