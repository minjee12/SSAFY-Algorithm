#include <iostream>
#include <vector>


using namespace std;

// 파이어볼 구조체
struct fire{
    // row, col, mass, speed, dir
    int r,c,m,s,d;
};


// 방향 direct
int dx[] = {0,1,1,1,0,-1,-1,-1};
int dy[] = {-1,-1,0,1,1,1,0,-1};

vector<fire> Map[50][50];

int N,M,K;

int main(){


    cin >> N >> M >> K;

    // 준비 상태의 파이어볼 벡터
    vector<fire> fireballs;

    for (int i=0; i<M; ++i){
        fire tmp;
        cin >>tmp.r >> tmp.c >> tmp.m >> tmp.s >> tmp.d;
        tmp.r--; // 첫 입력때 0~ N-1범위로 맞춰줌
        tmp.c--; // 첫 입력때 0~ N-1범위로 맞춰줌
        fireballs.push_back(tmp);
    }

    // 파이어볼의 이동
    int k = 0;

    while(k<K){
        // 1. 일단 준비된 애들부터 이동하기
        
        for (int i=0; i< fireballs.size(); ++i){
            fire* cur = &fireballs[i];
            // 이동 시(nx, ny 계산 ) 겁나 복잡하넹 

            int ny = (N + (cur->r + (dy[cur->d]*cur->s)%N))%N;
            int nx = (N + (cur->c + (dx[cur->d]*cur->s)%N))%N;  // 문제 가능성???

            // 위코드는 아무리 봐도 문제없는데ㅠㅠㅠㅠㅠㅠㅠㅠㅠ

            // 다음 위치로 파볼들 이동
            cur->r = ny; 
            cur->c = nx;

            // 이동 완료된 위치에 기록하기
            Map[ny][nx].push_back(*cur);
        }


        
        // 2. 이동 완료된 애들 처리

        vector<fire> new_balls; // 새로운 fireballs
        for(int i=0; i< fireballs.size(); ++i){

            fire *tmp = &fireballs[i];

            int cnt = Map[tmp->r][tmp->c].size();
            // 이동이 완료된 지점에 파볼 1개일 경우는 초기화만 수행
            // (추후 Map 메모리 부족 방지를 위해 clear대신 새 백터 할당)
            if(cnt==0) continue;
            if(cnt ==1) {
                new_balls.push_back(*tmp);
            }
            // 파볼 2개 이상
            else if(cnt > 1){
                vector<fire> cur_balls = Map[tmp->r][tmp->c];
                // cout << tmp->r <<" " <<tmp->c <<" " << cnt<<"\n";
                int new_m = 0, new_s = 0;
                bool even=true,odd=true;
                for (int i=0; i< cnt; ++i){

                    // 일단 더해
                    new_m += cur_balls[i].m;
                    new_s += cur_balls[i].s;
                    // 모든방향 짝수 또는 홀수 ==>
                    // 하나라도 짝수가 있으면 홀수는 아니고, 하나라도 홀수가 있으면 짝수가 아니고...
                    if(cur_balls[i].d%2==0){
                        odd = false;
                    }
                    if(cur_balls[i].d%2==1){
                        even = false;
                    }
                }
                
                // 소멸되지 않을 경우만 계산! -> 소멸될 경우에는 다음 턴에 이동할 파볼 리스트에 아예 추가하지 않음!
                if (new_m > 5) {
                    new_m/=5;
                    new_s/=cnt;

                    if(even || odd){ // 홀수만 또는 짝수만
                        for (int i=0; i< 8; i+=2){
                            fire nf = {tmp->r, tmp->c, new_m, new_s, i};
                            new_balls.push_back(nf);
                        }
                    }
                    else{ // 홀짝 섞여있을때
                        for (int i=1; i< 8; i+=2){ // 대각방향
                            fire nf = {tmp->r, tmp->c, new_m, new_s, i};
                            new_balls.push_back(nf);
                        }
                    }
                }

            }

            // 중복된 이동 제외를 위해 초기화! ( 이때, 메모리 공간도 같이 초기화!)
            // 단순이동(cnt==1) , 병합(cnt>=2)  및 소멸(M<5) 처리 완료된 지점 초기화
            // Map[tmp->r][tmp->c] = vector<fire>();
            Map[tmp->r][tmp->c].clear();
        }

        // 벡터 변수 교체 (이동 수행 준비가 된 파볼들 벡터)
        fireballs = new_balls;

        k++;
    }

    int sum =0;
    for (int i=0; i< fireballs.size(); ++i){
        sum += fireballs[i].m;
    }

    cout << sum <<"\n";


    return 0;
}