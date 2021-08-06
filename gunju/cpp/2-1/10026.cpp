#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <memory.h>

using namespace std;

char A[2][100][100];


int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};

int G[100][100];

int N;

void printG(){
    for(int i=0; i<N; ++i){
        for (int j = 0; j < N; ++j) {
            printf("%2d " ,G[i][j]);
        }
        cout <<"\n";
    }

    return;
}


/**
 * @brief
 *
 * @param y
 * @param x
 * @param color
 * @param group
 * @param blind (int) 0 : no-blind , 1 : blind
 */
void bfs(int y, int x, char color, int group, int blind){
    queue<pair<int,int> > q;
    q.push(make_pair(y,x));
    G[y][x] = group;


    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        int x = cur.second;
        int y = cur.first;
        int nx, ny;
        for(int i=0; i <4; ++i){
            ny = y+ dy[i];
            nx = x+ dx[i];
            if(nx>=0 && nx <N && ny >=0 && ny < N){
                if(G[ny][nx]==0 && A[blind][ny][nx]==color){
                    q.push(make_pair(ny,nx));
                    G[ny][nx]= group;
                }
            }
        }
    }

    return;
}

int main(){
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> A[0][i][j];
            if(A[0][i][j] =='G'){
                A[1][i][j] = 'R';
            }
            else{
                A[1][i][j] = A[0][i][j];
            }

        }
    }
    memset(G,0,sizeof(G));
    int g=1;
    // no blind
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(G[i][j]==0){
                bfs(i,j,A[0][i][j],g++,0);
            }
        }
    }

    //printG();
    cout << g-1 <<" ";
    g=1;
    memset(G,0,sizeof(G));
    // blind
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(G[i][j]==0){
                bfs(i,j,A[1][i][j],g++,1);
            }
        }
    }

    //printG();
    cout << g-1 <<"\n";

    return 0;
}