#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

int A[8][8];
bool chk[8][8];

int H ,W;


int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};



int main() {
    cin >> H >> W;

    for (int i=0; i <H; ++i){
        for (int j= 0; j <W; ++j){
            cin >> A[i][j];
        }
    }

    // count blanks
    int b_cnt = 0;

    for (int i=0; i<H; ++i){
        for (int j=0; j <W; ++j){
            if(A[i][j] == 0){
                b_cnt++;
            }
        }
    }

    int ans = 0; // max blanks;


    // 3개 벽 세운 후 BFS (바이러스 확산)  // 3중 for loop (모든 조합 경우의 수)
    // 2차원 배열 flatten -> 64**4 (~= 2천만)  < 2억 
    for (int a=0; a<H*W -2; ++a){
        for (int b = 1; b < H*W -1; ++b){
            for (int c = 2; c< H*W; ++c){
                if (A[a/W][a%W] !=0 || A[b/W][b%W] != 0 || A[c/W][c%W] !=0) continue;

                // 탐색 여부 초기화
                memset(chk, false, sizeof(chk));

                // 벽 세우고 
                A[a/W][a%W] = 1;
                A[b/W][b%W] = 1;
                A[c/W][c%W] = 1;
                // 탐색 (2를 확산 X =>  탐색가능한 범위의 누적합 계산)

                int v_cnt = 0;
                for(int i=0; i<H; ++i){
                    for (int j= 0; j <W; ++j){
                        if(!chk[i][j] && A[i][j] == 2){
                            v_cnt += bfs(i,j);
                        }
                    }
                }
                int safe = b_cnt - v_cnt -3; // 
                if( )


                //벽 허물고
                A[a/W][a%W] = 1;
                A[b/W][b%W] = 1;
                A[c/W][c%W] = 1;
            }


        }
    }
    

    



    return 0;
}