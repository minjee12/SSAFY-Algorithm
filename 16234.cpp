#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;

//#define PRINT

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

int A[50][50];
int C[50][50]; // 연합 구분 (초기값 0) (연합 : 1~ nxn)

int pop[2501];
//int gc[2501];

int N, L , R;


// DFS 또는 BFS로 연합 구분하기
// 하나의 연합에 대해 generation 내의 연합 통합 후 찾기 (check or C)
// 연합 체크 및 연합 크기 누적, 연합 개수 계산

// 탐색함수 : 수행 시 연합 크기체크 및 연합 번호 선정

// generation 종료 조건
// 연합 변경 시 flag =true; (default : false)

bool update_check(int max_group){
    bool change = false;
    for(int i=0; i< N; ++i){
        for (int j = 0; j < N; ++j) {

            // 비효율적인 3중 for문 ㅠㅠㅠㅠ

            /*
            for(int g = 1; g<=max_group; ++g) {
                if (gc[g]!=1 &&C[i][j] == g) {
                    if(A[i][j] != pop[g]) {
                        A[i][j] = pop[g];
                        change = true;
                    }
                }
            }
             */
            if(A[i][j] != pop[C[i][j]]){
                A[i][j] = pop[C[i][j]];
                change = true;
            }
        }
    }
    return change;
}


int bfs(pair<int,int> coord, int group){

    int a_sum=0, g_cnt=0;

    queue<pair<int,int> > q;
    q.push(coord);
    C[coord.first][coord.second] = group;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        a_sum += A[y][x];
        g_cnt++;

        int nx, ny;
        int gap;
        for (int k=0; k<4; ++k){
            nx = x+dx[k];
            ny = y+dy[k];
            if(nx >=0 && nx <N && ny >=0 && ny <N){
                //gap = (A[ny][nx] -A[y][x])<0 ? -A[ny][nx] +A[y][x] :A[ny][nx] -A[y][x];

                // c++ abs 자체 제공(std library)
                gap = abs(A[ny][nx] -A[y][x]);
                if(gap >= L && gap <= R && C[ny][nx]==0){
                    C[ny][nx]= group;
                    q.push(make_pair(ny,nx));
                }
            }
        }
    }
    //gc[group] = g_cnt;

    return (int)(a_sum/g_cnt);
}


int main(){

    cin >> N >> L >> R;

    for (int i=0; i < N; ++i){
        for (int j=0; j <N; ++j){
            cin >> A[i][j];
        }
    }

    int ans = 0;
    while(true){ // generation
        // C initialize(초기화)
        for(int i=0; i<N; ++i){
            memset(C[i], 0, sizeof(C[i]));
        }

        int group_cnt= 0;
        for (int i=0; i<N; ++i){
            for (int j=0; j<N; ++j){
                if(C[i][j] ==0){
                    int new_pop = bfs(make_pair(i,j), ++group_cnt);
                    pop[group_cnt]= new_pop; // 그룹당 갱신된 인구수
                }
            }
        }

        // end 조건 : 이전 인구와 갱신된 인구가 전혀 변하지 않았을 때!
        if(!update_check(group_cnt)) break;


// 디버깅용 print code
#ifdef PRINT
        for (int i=0; i < N; ++i){
            for(int j=0; j <N; ++j) {
                cout << C[i][j] <<" ";
            }
            cout << "\n";
        }

        for (int i=0; i < N; ++i){
            for(int j=0; j <N; ++j) {
                cout << A[i][j] <<" ";
            }
            cout << "\n";
        }
#endif

        ans++;
    }

    cout << ans <<"\n";

    return 0;
}