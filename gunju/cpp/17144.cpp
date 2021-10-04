#include <iostream>
#include <cstring>
#include <queue>

//#define DEBUG

using namespace std;

int R, C, T;

int Map[50][50];

int dx[] = {0,-1,0,1};
int dy[] = {-1,0,1,0};

int cleaner[2];

struct pos{
    int y,x;
    int dust;
};

#ifdef DEBUG
void print_map(char type){
    if(type=='s') printf("After Speard \n" );
    else if(type=='c') printf("After Clean \n");
    for (int r=0; r<R; ++r){
        for (int c=0; c<C; ++c){
            printf("%d ", Map[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}
#endif


// 미세먼지 확산
void spread(){
    // 미세먼지 위치 확인 -> 큐에 담기
    queue<pos> q;
    for (int r=0; r<R; ++r){
        for (int c=0; c<C; ++c){
            if(Map[r][c]>0) {
                pos tmp = {r,c, Map[r][c]};
                q.push(tmp);
            }
        }
    }
    // Map clear + 공기청정기 위치 적용
    memset(Map, 0, sizeof(Map));
    Map[cleaner[0]][0]=-1;
    Map[cleaner[1]][0]=-1;

    // 순차적으로 미세먼지 누적하기
    while(!q.empty()){
        pos cur= q.front();
        q.pop();

        int cnt =0;
        int ny,nx;
        int p_dust = cur.dust /5;

        if(p_dust > 0){
            for (int i=0; i<4; ++i){
                ny = cur.y + dy[i];
                nx = cur.x + dx[i];
                if(ny < 0 || ny >= R || nx < 0 || nx >= C || Map[ny][nx]==-1) continue;

                cnt++;
                Map[ny][nx] += (cur.dust /5);
            }
        }
        Map[cur.y][cur.x] += cur.dust - (p_dust * cnt);
    }

    return;
}

// 공기청정기 작동
void clean(){
    int e_tmp, s_tmp=0; // 다음 방향 넘어가기전에 임시 저장용 버퍼

    // 상부 청정기 바람 
    int up_r = cleaner[0];
    // →→→→→
    e_tmp = Map[up_r][C-1];
    for (int c=C-1; c>1; --c){
        Map[up_r][c] = Map[up_r][c-1];
    }
    Map[up_r][1] = s_tmp;
    s_tmp = e_tmp;

    // ↑↑↑↑↑
    e_tmp = Map[0][C-1];
    for (int r=0; r<up_r; ++r){
        Map[r][C-1] = Map[r+1][C-1];
    }
    Map[up_r-1][C-1]=s_tmp;
    s_tmp = e_tmp;

    // ←←←←←
    e_tmp = Map[0][0];
    for (int c=0; c<C-1; ++c){
        Map[0][c] = Map[0][c+1];
    }
    Map[0][C-2]=s_tmp;
    s_tmp = e_tmp;

    // ↓↓↓↓↓
    for (int r=up_r-1; r>0; --r){
        Map[r][0] = Map[r-1][0];
    }
    if(up_r >1) Map[1][0]=s_tmp;


    // 하부 청정기 바람
    int down_r = cleaner[1];
    // →→→→→
    e_tmp = Map[down_r][C-1];
    for (int c=C-1; c>1; --c){
        Map[down_r][c] = Map[down_r][c-1];
    }
    Map[down_r][1] = 0;
    s_tmp = e_tmp;

    // ↓↓↓↓↓
    e_tmp = Map[R-1][C-1];
    for (int r=R-1; r>down_r+1; --r){
        Map[r][C-1] = Map[r-1][C-1];
    }
    Map[down_r+1][C-1]=s_tmp;
    s_tmp = e_tmp;

    // ←←←←←
    e_tmp = Map[R-1][0];
    for (int c=0; c<C-1; ++c){
        Map[R-1][c] = Map[R-1][c+1];
    }
    Map[R-1][C-2]=s_tmp;
    s_tmp = e_tmp;

    // ↑↑↑↑↑ 
    for (int r=down_r+1; r<R-1; ++r){
        Map[r][0] = Map[r+1][0];
    }
    if(R-2>down_r) Map[R-2][0]=s_tmp;


    return;
}

// 남은 먼지 계산
int calc_dust(){
    int sum =0;
    for (int r=0; r< R; ++r){
        for(int c=0; c< C; ++c){
            if(c==0 && (r==cleaner[0] || r==cleaner[1])) continue;
            sum += Map[r][c];
        }
    }
    return sum;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> R >> C >> T;

    int c_idx=0;
    for (int r=0; r<R; ++r){
        for (int c=0; c<C; ++c){
            cin >> Map[r][c];
            if(Map[r][c]==-1) cleaner[c_idx++]=r;
        }
    }

    for (int t=0; t<T; ++t){
        spread();
#ifdef DEBUG
        print_map('s');
#endif
        clean();
#ifdef DEBUG
        print_map('c');
#endif

    }
    int ans = calc_dust();

    printf("%d\n",ans);

    return 0;
}