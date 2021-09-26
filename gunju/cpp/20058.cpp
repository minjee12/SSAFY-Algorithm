#include <iostream>
#include <vector>

using namespace std;

int twos[] = {1,2,4,8,16,32,64};
int N, Q;


int Ice[64][64];

// 구현해야 하는 함수들
    // 1. 격자 나누기 (div_row, div_col)
        // div_row 짝수(0~) : div_col 짝수(0~)번째
        // div_row 홀수(1~) : div_col 홀수(1~)번째
    // 2. 격자들 로테이션 (1번 루프 내부에서 수행)
        // 시계방향 rotation 
        // 격자 값 copy -> original[y][x] = copy[x][(격자크기-1) -y]
    // 3. (모든 Ice 배열값에 대해) 인접여부 체크 및 얼음크기 감소
        // 일단 양 끝 모서리 4개는 최대 2개 인접이라 무조건 감소
        // 상하좌우 4개중 3개 이상일때만 4개는

    // 4. 최대 덩어리 
        // 1) -> 마지막에 유니온파인드 -> 서로다른 덩어리 최대개수 약 1024
        // 2) BFS + visited로 연결 그래프 확인


void divide_rotate(int q){
    int sz = twos[q];
    int tot_sz = twos[N];

    int M = tot_sz/sz;

    for (int i=0; i < M; ++i){
        for (int j=0; j<M; ++j){
            if((i%2==0 && j%2==0) || (i%2==1 && j%2 ==1) ){ // tile 인덱스 짝짝 또는 홀홀
                vector<vector<int> > tmp(sz, vector<int>(sz,0)); // copy용 임시 버퍼
                
                // 회전
                for (int r=0; r<sz; ++r){
                    for (int c=0; c<sz; ++c){
                        tmp[r][c] = Ice[i*sz + c][j*sz + (sz-1)-r];
                    }
                }

                // 원본 Ice에 복사
                for (int r=0; r<sz; ++r){
                    for (int c=0; c<sz; ++c){
                        Ice[i*sz + r][j*sz + c] = tmp[r][c];
                    }
                }
            }
        }
    }

    return;
}



// 얼음 녹는거 계산~~
void check_ice(){


    return;
}


// 유니온파인드 용 함수


int main(){
    
    cin >> N >> Q;

    for (int i=0; i< twos[N]; ++i){
        for (int j=0; j< twos[N]; ++j){
            cin >> Ice[i][j];
        }
    }

    // q만큼 격자화 + 로테이션 + 얼음 녹는 처리
    for (int i=0; i< Q; ++i){
        int q;
        cin >> q;
        


    }


    // 유니온파인드 또는 연결요소찾기(DFS, BFS) -> map으로 연결요소 크기 계산




    return 0;
}