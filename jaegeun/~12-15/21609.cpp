// 상어 중학교
// https://www.acmicpc.net/problem/21609

/*
*   무지개 블록에 주의하자!!
*/

#define MAX_SIZE 20
#define EMPTY -2

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

typedef struct {
    int g_size;  // 그룹 사이즈
    int r_cnt; // 무지개 블록 사이즈
    int row; // 기준 블록 행
    int col; // 기준 블록 열
    int num; // 방문 기록 번호
}group_info;

int N, M; // 격자 크기, 색상 개수
int score = 0;
int board[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

bool compair(group_info a, group_info b) {
    if (a.g_size == b.g_size) {
        if (a.r_cnt == b.r_cnt) {
            if (a.row == b.row) return a.col > b.col;
            else return a.row > b.row;
        }
        else return a.r_cnt > b.r_cnt;
    }
    else return a.g_size > b.g_size;
}

group_info find_group(int x, int y, int idx) {
    bool temp[MAX_SIZE][MAX_SIZE] = { 0, };

    queue<pair<int, int>>q;
    int block_cnt = 1;
    int rainbow_cnt = 0;
    int st = board[x][y];
    temp[x][y] = true;
    q.push({ x, y });

    while (q.size()) {
        int cx = q.front().first;
        int cy = q.front().second;

        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue; // 범위 아웃
            if (visited[nx][ny] >= 0) continue; // 이미 방문
            if (temp[nx][ny]) continue;
            if (board[nx][ny] == st || board[nx][ny] == 0) {
                if (board[nx][ny] == 0) rainbow_cnt++;
                temp[nx][ny] = true;
                q.push({ nx, ny });
                block_cnt++;
            }
        }
    }
    if (block_cnt >= 2) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (temp[i][j] && board[i][j] != 0) visited[i][j] = idx;
            }
        }
        return { block_cnt, rainbow_cnt, x, y, idx };
    }
    return { 0, 0, x, y, -1 };
}

void get_groups(vector<group_info>& g) {
    for (int i = 0; i < N; i++) {
        fill(visited[i], visited[i] + N, -1);
    }

    int g_cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (visited[i][j] == -1 && board[i][j] >= 1) {
                group_info group = find_group(i, j, g_cnt);
                if (group.g_size >= 2) {
                    g.push_back(group);
                    g_cnt++;
                }
            }
        }
    }
}

void gravity() {
    int temp[MAX_SIZE][MAX_SIZE] = { 0, };
    for (int i = 0; i < N; i++) {
        fill(temp[i], temp[i] + MAX_SIZE, -2);
    }

    for (int i = 0; i < N; i++) {
        int base = N - 1;
        for (int j = N - 1; j >= 0; j--) {
            if (board[j][i] >= 0) {
                temp[base][i] = board[j][i];
                base--;
            }
            if (board[j][i] == -1) {
                temp[j][i] = -1;
                base = j - 1;
            }
        }
    }
    memcpy(board, temp, sizeof(board));
}

void rotate_board() {
    int temp[MAX_SIZE][MAX_SIZE];
    memcpy(temp, board, sizeof(board));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = temp[j][N - 1 - i];
        }
    }
}
void remove_block(int x, int y) {
    queue<pair<int, int>>q;
    q.push({ x, y });

    int st = board[x][y];
    board[x][y] = EMPTY;

    while (q.size()) {
        int cx = q.front().first;
        int cy = q.front().second;

        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue; // 범위 아웃
            if (board[nx][ny] == st || board[nx][ny] == 0) {
                board[nx][ny] = EMPTY;
                q.push({ nx,ny });
            }
        }
    }
}

void solve() {
    while (true) {
        vector<group_info> groups;
        get_groups(groups);
        if (groups.size() == 0) break;
        sort(groups.begin(), groups.end(), compair);
        int rm_num = groups[0].num;
        score += groups[0].g_size * groups[0].g_size;
        remove_block(groups[0].row, groups[0].col);
        gravity();
        rotate_board();
        gravity();
    }
    cout << score;
}

int main() {
    freopen_s(new FILE*, "text.txt", "r", stdin);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }
    solve();
    return 0;
}