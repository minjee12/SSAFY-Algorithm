#include <iostream>
#include <vector>
#include <limits>
#include <cstring>

//#define DEBUG

// d1,d2 가능한 범위 구하는것!

// 재귀로 구현시 -> x,y,d1,d2 매개변수로.. -> 구역 나누기 -> 가장많은곳 - 가장적은곳 (전역변수와 비교)
// 근데 재귀로 구현하면 x,y,d1,d2각각에 대해 4차원 visited 배열을 필요로 할듯... 
// 그냥 for loop으로 구현하는게 맞아보임
// x,y -> d1,d2 ==> 4중 for loop (서로다른 x,y,d1,d2에 대해 중복없음)

// 문제가 좀 역겨움... (r,c) 로 표현되므로 (x,y) 에서 x가 세로, y가 가로를 의미함

using namespace std;

int N;

int Map[20][20]; // 각 구역의 유권자수
#ifdef DEBUG
int Div_Map[20][20]; // (디버깅용)경계그리는 용도의 메모리
#endif 

int min_dist = numeric_limits<int>::max();


//x,y,d1,d2 입력받아 경계를 나누고 && 각 경계크기를 계산하는 함수
void div_compute(int x, int y, int d1, int d2){
    #ifdef DEBUG
    // 초기화
    memset(Div_Map, 0, sizeof(Div_Map));
    #endif

    int cnt[5] = {0,0,0,0,0};

    // 구역 할당 및 구역 크기 계산 (if 문)
        // 일단 if else 문으로 쭉 해보고 else처리로 5구역이 나눠지는지 해보기 -> 안되면 다른 방식
    #ifdef DEBUG
    printf ("\n==  x: %d, y:%d, d1:%d, d2:%d ==\n", x,y,d1,d2);
    #endif

    for (int r=0; r< N; ++r){
        for (int c=0; c < N; ++c){
            if(r >=0 && r< x+d1 && c >=0 && c <= y && r+c < x+y){
                cnt[0]+= Map[r][c];
                #ifdef DEBUG
                Div_Map[r][c] = 1;
                #endif
            }
            else if(r>=0 && r<=x+d2 && c >y && c <N && c-r > y-x){
                cnt[1]+= Map[r][c];
                #ifdef DEBUG
                Div_Map[r][c] =2;
                #endif
            }
            else if (r >= x+d1 && r < N && c >=0 && c < y-d1+d2 && c-r < y-x - d1*2){
                cnt[2]+= Map[r][c];
                #ifdef DEBUG
                Div_Map[r][c] = 3;
                #endif
            }
            else if (r >x+d2 && r<N && c >= y-d1+d2 && c < N && r+c > x+y+d2*2){
                cnt[3]+= Map[r][c];
                #ifdef DEBUG
                Div_Map[r][c] = 4;
                #endif
            }
            else{
                cnt[4]+= Map[r][c];
                #ifdef DEBUG
                Div_Map[r][c] = 5;
                #endif
            }
        }
    }


    // 구역 최댓값 - 구역 최솟값 계산 후 min_dist와 비교
    int max_cnt = *max_element(cnt, cnt+5);
    int min_cnt = *min_element(cnt, cnt+5);

    int dist = max_cnt-min_cnt;

    min_dist = (dist < min_dist) ? dist : min_dist;

    #ifdef DEBUG
    printf("\n");
    for (int i=0; i< N; ++i){
        for (int j=0; j <N; ++j){
            printf("%d ", Div_Map[i][j]);
        }
        printf("\n");
    }
    #endif

    return;
}


// 설정된 기준점(x,y)로부터 가능한 d1,d2 설정하여 계산하는 함수
void set_dd(int x, int y){
    // d1 정한 후 d2 정하기
    
    // d1최댓값 = min(y ,N-1 - x -1(d2최솟값) );
    // d2최댓값 = min(N-1-x-d1, N-1 -y);
    int max_d1 = min(y, N-1 -x - 1);

    int max_d2;
    for (int d1=1; d1 <= max_d1; ++d1){
        max_d2 = min(N-1-x-d1, N-1 -y);
        for (int d2=1; d2<=max_d2; ++d2){
            div_compute(x,y,d1,d2);
        }
    }
    return;
}



// 가능한 (x,y) 기준점 설정하는 함수
void set_xy(){
    // 여기서 x는 세로! , y는 가로임을 명심
    // x,y는 경계선의 맨 꼭대기 점
    // y(가로)는 d1보다는 커야하므로 1(d1최솟값)<= y < N-1(d2최솟값)
    // x(세로)는 0 <= x < N-2 (d1==1 && d2==1 <최솟값>)
    
    for (int i=0; i< N-2; ++i){   // x(row)
        for (int j=1; j < N-1; ++j) { // y(col)
            set_dd(i,j);
        }
    }
    return;
}


int main(){
    cin >> N;

    for (int i=0; i< N; ++i){
        for (int j=0; j< N; ++j){
            cin >> Map[i][j];
        }
    }

    set_xy();

    printf("%d\n",min_dist);

    return 0;
}