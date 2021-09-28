#include <iostream>
#include <vector>
#include <queue>

//#define PRINT

using namespace std;

int twos[] = {1,2,4,8,16,32,64};
int N, Q;


int dy[] = {0,0,-1,1};
int dx[] = {-1,1,0,0};


int Ice[64][64];

int G[64][64]; // group

bool visited[64][64]; // visited for BFS

int max_ice=0;

#ifdef PRINT
void debug_print(){
    int NN = twos[N];
    cout <<"\n";
    for (int i=0; i< NN; ++i){
        for (int j=0; j<NN; ++j){
            cout << Ice[i][j] <<" ";
        }
        cout <<"\n";
    }
    return;
}
#endif

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
            // 문제 이해 잘못함.... ㅠㅠㅠ
            //if((i%2==0 && j%2==0) || (i%2==1 && j%2 ==1) ){ // tile 인덱스 짝짝 또는 홀홀
                vector<vector<int> > tmp(sz, vector<int>(sz,0)); // copy용 임시 버퍼
                
                // 회전
                for (int r=0; r<sz; ++r){
                    for (int c=0; c<sz; ++c){
                        tmp[r][c] = Ice[i*sz + r][j*sz + c];
                    }
                }

                // 원본 Ice에 복사
                for (int r=0; r<sz; ++r){
                    for (int c=0; c<sz; ++c){
                        Ice[i*sz + r][j*sz + c] = tmp[(sz-1)-c][r];
                    }
                }
            //}
        }
    }

    return;
}



// 얼음 녹는거 처리~~
void melt_ice(){
    int NN = twos[N];

    int new_Ice[64][64];

    int ny, nx;
    for (int i=0; i< NN; ++i){
        for (int j=0; j< NN; ++j){
            if(Ice[i][j]==0) {
                new_Ice[i][j] = Ice[i][j];
                continue;
            }

            int cnt = 0;
            for (int k=0; k<4; ++k){
                ny = i+ dy[k];
                nx = j+ dx[k];
                if(nx>=0 && nx < NN && ny>=0 && ny< NN && Ice[ny][nx] >0){
                    cnt++;
                }
            }
            if(cnt <3) new_Ice[i][j] = Ice[i][j]-1;
            else new_Ice[i][j] = Ice[i][j];
        }
    }
    
    
    for (int i=0; i< NN; ++i){
        for (int j=0; j<NN; ++j){
            Ice[i][j] = new_Ice[i][j];
        }
    }
    
    return;
}

// 남은 얼음 개수
int num_ices(){
    int NN = twos[N];
    int res = 0;
    for (int i=0; i< NN; ++i){
        for (int j=0; j<NN; ++j){
            res += Ice[i][j];
        }
    }
    return res;
}


// BFS (연결요소 개수) -> 시간 되나?
void ice_group_count(int y, int x){
    queue<pair<int,int> > q;

    int cnt = 1;
    q.push(make_pair(y,x));
    visited[y][x] =true;

    while(!q.empty()){
        auto cur = q.front();
        q.pop();

        int ny,nx;
        for (int i=0; i<4; ++i){
            ny = cur.first + dy[i];
            nx = cur.second + dx[i];
            if(ny<0 || ny >= twos[N] || nx <0 || nx >=twos[N] || visited[ny][nx]) continue;
            if(Ice[ny][nx]==0) continue;
            q.push(make_pair(ny,nx));
            visited[ny][nx] = true;
            cnt++;
        }
    }

    if(max_ice < cnt) max_ice= cnt;
    return;
}




int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

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

        #ifdef PRINT 
        debug_print();
        #endif
        
        divide_rotate(q);

        #ifdef PRINT 
        debug_print();
        #endif

        melt_ice(); 
    }

    int total = num_ices();

    cout << total <<"\n";

    // 유니온파인드 또는 연결요소찾기(DFS, BFS) -> map으로 연결요소 크기 계산

    for (int i=0; i< twos[N]; ++i){
        for (int j=0; j < twos[N]; ++j){
            if(Ice[i][j]!=0 && !visited[i][j]){
                ice_group_count(i,j);
            }
        }
    }

    cout << max_ice <<"\n";



    return 0;
}