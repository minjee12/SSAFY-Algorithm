#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

int A[50][50];
int C[50][50]; // 연합 구분 (초기값 0) (연합 : 1~ nxn)

int N, L , R;


// DFS 또는 BFS로 연합 구분하기 
    // 하나의 연합에 대해 generation 내의 연합 통합 후 찾기 (check or C)
    // 연합 체크 및 연합 크기 누적, 연합 개수 계산

// 탐색함수 : 수행 시 연합 크기체크 및 연합 번호 선정

// generation 종료 조건
    // 연합 변경 시 flag =true; (default : false)


int bfs(pair<int,int> coord, int group){

    queue<pair<int,int> > q;
    q.push(coord);

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        int nx, ny;
        int gap;
        for (int k=0; k<4; ++k){
            nx = x+dx[k];
            ny = y+dy[k];
            gap = abs(A[ny][nx] -A[y][x]);

            if(nx >=0 && nx <N && ny >=0 && ny <N){
                if(gap > L && gap < R && C[nx][ny]==0){
                    C[nx][ny]= group;
                    q.push(make_pair(ny,nx));
                }
            }
        }
        

    }




}


int main(){

    cin >> N >> L >> R;

    for (int i=0; i < N; ++i){
        for (int j=0; j <N; ++j){
            cin >> A[i][j];
        }
    }


    while(true){ // generation
        int group_cnt= 1;
        for (int i=0; i<N; ++i){
            for (int j=0; j<N; ++j){
                if(C[i][j] !=0 ){
                    bfs(make_pair(i,j), group_cnt++);
                }
            }
        }

        if(group_cnt==(N*N)) break; // 연합 크기 max ==1 일때
    }






    return 0;
}