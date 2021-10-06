#include <iostream>
#include <cstring>


using namespace std;


int dx[] = {1,0,-1,0};
int dy[] = {0,-1,0,1};

struct gen{
    int x,y,d,g;
}G[20];

int dList[1024];

int twos[11] = {1,2,4,8,16,32,64,128,256,512,1024};

// 유효범위 좌표 0<=x,y<=100
bool Map[101][101];

void print_map(){
    for (int i=0; i<10; ++i){
        for (int j=0; j<10 ;++j){
            if(Map[i][j]) printf("o ");
            else printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

void make_gen_list(int d, int g){
    memset(dList, 0, sizeof(dList));
    dList[0] = d;
    if(g==0) {
        return;
    }
    int tmp=0;
    while(tmp<g){
        for (int i=twos[tmp], j=1; i<twos[tmp+1]; ++i,++j){
            dList[i]=(dList[twos[tmp]-j]+1)%4;
        }
        tmp++;
    }

    return;
}

// 드래곤 커브 그리기
void draw_curve(int idx){
    gen cur = G[idx];

    make_gen_list(cur.d,cur.g);

    int cy=cur.y;
    int cx=cur.x;
    Map[cy][cx] = true;

    //printf("[%d] ",cur.g);
    for (int i=0; i< twos[cur.g]; ++i){
        //printf("%d ", dList[i]);
        cy += dy[dList[i]];
        cx += dx[dList[i]];
        Map[cy][cx] = true;
    }
    //printf("\n");


    return;
}




int sdy[] = {0,0,1,1};
int sdx[] = {0,1,0,1};
// 사각형 개수 세기
int count_square(){
    int cnt =0;
    bool chk;
    for (int i=0; i<100; ++i){
        for (int j=0; j< 100; ++j){
            chk=true;
            for (int k=0; k<4; ++k){
                if(!Map[i+sdy[k]][j+sdx[k]]) chk=false;
            }
            if(chk) cnt++;
        }
    }
    return cnt;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    for (int i=0; i< N; ++i){
        cin >> G[i].x >>G[i].y >> G[i].d >> G[i].g;
        draw_curve(i);
    }
    //print_map();

    int ans = count_square();

    printf("%d\n",ans);

    return 0;
}