// 모노미노도미노 2
// https://www.acmicpc.net/problem/20061


#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N;
int score = 0;

class board {
private:
    int m_board[6][4] = { 0, };
    int m_score = 0;

public:
    board() { }
    int get_score() { return m_score; }

    int get_remain_block() {
        int cnt = 0;
        for (int i = 2; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (m_board[i][j]) cnt++;
            }
        }
        return cnt;
    }

    void print_board() {
        for (int i = 0; i < 6; i++) {
            if (i == 2) cout << "--\n";
            for (int j = 0; j < 4; j++) {
                if (m_board[i][j]) cout << "■ ";
                else cout << "□ ";
            }
            cout << "\n";
        }
        cout << "==\n";
    }

    // 행 삭제
    void delete_row(int row) {
        m_score += 1;
        memset(m_board[row], 0, sizeof(m_board[row])); // 행 요소 삭제
        int temp[6][4] = { 0, };
        // row번째 열까지 조사, 한칸씩 내림
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < 4; j++) {
                if (m_board[i][j]) {
                    temp[i + 1][j] = 1;
                }
            }
        }
        // row번째 열부터는 그대로 복사
        for (int i = row; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (m_board[i][j]) {
                    temp[i][j] = 1;
                }
            }
        }
        memcpy(m_board, temp, sizeof(m_board));
    }

    // 연한 칸 조사
    void check_light() {
        int r_cnt = 0;
        bool flag = false;
        for (int i = 1; i >= 0; i--) {
            for (int j = 0; j < 4; j++) {
                if (m_board[i][j]) {
                    r_cnt = i;
                    flag = true;
                    break;
                }
            }
        }
        if (flag) { // 연한 칸에 블럭이 있음
            int temp[6][4] = { 0, };
            if (r_cnt == 1) { // 1줄 삭제
                memset(m_board[5], 0, sizeof(m_board[5]));
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (m_board[i][j]) temp[i + 1][j] = 1; // 1줄 내림
                    }
                }
            }
            else if (r_cnt == 0) { // 2줄 삭제
                memset(m_board[5], 0, sizeof(m_board[5]));
                memset(m_board[4], 0, sizeof(m_board[4]));
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (m_board[i][j]) temp[i + 2][j] = 1; // 2줄 내림
                    }
                }
            }
            memcpy(m_board, temp, sizeof(m_board));
        }
    }

    // 행 조사
    bool check_row(int row) {
        for (int i = 0; i < 4; i++) {
            if (m_board[row][i] == 0) return false;
        }
        return true;
    }

    // 블럭 채우기
    void fill(vector<pair<int, int>> block, int type) {
        int target_idx = 6;

        // 열을 기준으로, 채워져 있는 인덱스를 찾음
        for (int i = 0; i < block.size(); i++) {
            int by = block[i].second;
            for (int j = 5; j >= 0; j--) {
                if (m_board[j][by]) {
                    target_idx = min(j, target_idx);
                }
            }
        }

        int target_row = target_idx - 1; // 채워진 블록 위로 채움

        for (int i = 0; i < block.size(); i++) {
            if (type == 1) { // 1 x 1
                m_board[target_row][block[i].second] = 1;
            }
            else if (type == 2) { // 1 x 2
                m_board[target_row][block[i].second] = 1;
            }
            else { // 2 x 1
                m_board[target_row - i][block[i].second] = 1;
            }
        }
    }
};


void solve() {
    board Green = board();
    board Blue = board();
    int n; cin >> n;
    int t, x, y;
    for (int i = 0; i < n; i++) {
        cin >> t >> x >> y;
        vector<pair<int, int>> green_blocks;
        vector<pair<int, int>> blue_blocks;
        if (t == 1) { // 1 x 1 
            green_blocks.push_back({ x, y });
            blue_blocks.push_back({ y, 3 - x });
        }
        else if (t == 2) { // 1 x 2 가로
            green_blocks.push_back({ x, y });
            green_blocks.push_back({ x, y + 1 });
            blue_blocks.push_back({ y, 3 - x });
            blue_blocks.push_back({ y + 1, 3 - x });
        }
        else { // t == 3  2 x 1 세로
            green_blocks.push_back({ x, y });
            green_blocks.push_back({ x + 1, y });
            blue_blocks.push_back({ y, 3 - x });
            blue_blocks.push_back({ y, 2 - x });
        }

        // 블럭 채우기
        Green.fill(green_blocks, t);
        if (t == 2) Blue.fill(blue_blocks, 3);
        else if (t == 3) Blue.fill(blue_blocks, 2);
        else Blue.fill(blue_blocks, 1);

        // 다 채워진 열 지우기
        for (int i = 5; i >= 2; i--) {
            while (Green.check_row(i)) Green.delete_row(i);
            while (Blue.check_row(i)) Blue.delete_row(i);
        }

        // 연한 칸 지우기
        Green.check_light();
        Blue.check_light();
    }

    cout << Green.get_score() + Blue.get_score() << "\n";
    cout << Green.get_remain_block() + Blue.get_remain_block() << "\n";

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen_s(new FILE*, "text.txt", "r", stdin);
    solve();
    return 0;
}