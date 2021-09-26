#include <iostream>
#include <vector>
#include <algorithm>

//#define PRINT

    // 달팽이 움직임 수식
        // 2회 방향전환 후 방향당 전진거리(len) 1씩 증가
        // 방향은 ← ↓ → ↑ 순서대로 진행되며 처음과 마지막은 ←
        // 이동 횟수 = N^2 -1

    // 모래 움직임
        // ratio 행렬의 경우 dir 값 (0~3) 에 따라 방향변함
        // 1. 먼저 바람이 움직임
        // 2. 바람이 움직인 곳(y)값을 기준으로 ratio 곱을 활용해 주변에 모래 분산
        // 3. ny,nx > N 또는 ny,nx < 0 일경우 ans에 누적


using namespace std;

int N;
int sand[499][499];

// 디버깅 함수 존
#ifdef PRINT
void print_sand(){
    cout <<"\n";
    for (int i=0; i< N; ++i){
        for (int j=0 ; j<N; ++j){
            cout << sand[i][j] <<" ";
        }
        cout <<"\n";
    }
}
#endif

// 소수점 아래는 버리므로 int 비율 계산은 s[y][x] = s[i][j]*ratio[y][x]/100 으로 수행
// -1 : alpha ==> 직관적으로 생각하면 75%라고 생각할 수 있지만, 소수점 아래는 버리기 때문에 확률에 변동이 생김
int ratios[4][5][5] = {
    { // 왼쪽
    {0, 0, 2, 0, 0},
    {0,10, 7, 1, 0},
    {5, 0, 0, 0, 0},
    {0,10, 7, 1, 0},
    {0, 0, 2, 0, 0}
    },
    { // 아래쪽
    {0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {2, 7, 0, 7, 2},
    {0,10, 0,10, 0},
    {0, 0, 5, 0, 0}
    },
    { // 오른쪽
    {0, 0, 2, 0, 0},
    {0, 1, 7,10, 0},
    {0, 0, 0, 0, 5},
    {0, 1, 7,10, 0},
    {0, 0, 2, 0, 0}
    },
    { // 위쪽
    {0, 0, 5, 0, 0},
    {0,10, 0 ,10, 0},
    {2, 7, 0, 7, 2},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0}
    }
};


int dx[]= {-1,0,1,0};
int dy[]= {0,1,0,-1};

int ans = 0;



void blow_sand(int ty, int tx, int dir){
    // y는 고정 변수
    int y = sand[ty][tx];

    // 알파는 가변 변수
    int alpha = y;
    // alpha's position = (ty+dy[dir] , tx+dx[dir])

    // cout <<ty << ","<< tx <<"|" << y <<" " << alpha <<"\n";

    // ty, tx ==>> (2,2) 기준
    for (int i=-2; i<=2; ++i){
        for (int j=-2; j<=2; ++j){
            if(ratios[dir][i+2][j+2] > 0){
                
                int tmp = (y*ratios[dir][i+2][j+2])/100;
                
                alpha -= tmp;
                #ifdef PRINT
                if (ty==1 && tx ==0) {
                    cout <<"tmp : " << tmp << ", alpha : "<< alpha <<"\n";
                }
                #endif

                // 나갔을때!
                if(ty+i < 0 || ty+i >=N || tx+j <0 || tx+j >=N){
                    ans += tmp;
                }
                else{
                    sand[ty+i][tx+j] += tmp;
                }
            }
        }
    }

    // y 처리
    sand[ty][tx] = 0; // y는 0이 되었어요

    // alpha 처리

    int ay = ty+dy[dir], ax = tx+dx[dir];
    // cout << "a : " << alpha << " (" << ay <<" , " << ax <<")\n";
    if(ay < 0 || ay >= N || ax < 0 || ax >= N){
        ans += alpha;
    }
    else{
        sand[ty+dy[dir]][tx+dx[dir]] += alpha;
    }

    return;
}



void move(){
    int cy = N/2, cx = N/2;

    int cnt=0;
    int len=1;
    int dir =0;

    int change =0;

    // N제곱 -1 회만큼만 이동
    while(cnt < N*N -1){

        for (int i=0; i< len; ++i){
            if(cnt >= N*N-1) break;
            cy += dy[dir];
            cx += dx[dir];

            blow_sand(cy,cx,dir);
#ifdef PRINT
            cout << "cnt : " << cnt <<"\n";
            print_sand();
            cout << "ans : " <<ans <<"\n";
#endif

            cnt++;
        }

        change++;
        if(change%2 ==0) {
            len++;
        }
        dir = (dir+1)%4;
    }

    return;
}




int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    for (int i=0; i< N; ++i){
        for (int j=0; j <N; ++j){
            cin >> sand[i][j];
        }
    }

    move();

    cout << ans <<"\n";


    return 0;
}