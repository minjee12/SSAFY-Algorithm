#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace  std;

int A[50][50];

int H,W;

int dx[] = {-1,-1,-1,0,0,1,1,1};
int dy[] = {-1,0,1,-1,1,-1,0,1};

int calc_dist(int y, int x){
    vector<vector<int> > dist(H,vector<int>(W,-1));
    dist[y][x]=0;

    queue<pair<int,int> > q;
    q.push(make_pair(y,x));

    while(!q.empty()){
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();
        int ny, nx;
        for (int i=0; i <8; ++i){
            ny = cur_y + dy[i];
            nx = cur_x + dx[i];
            if(ny <H && ny >=0 && nx <W && nx>=0 && dist[ny][nx]==-1){
                dist[ny][nx] = dist[cur_y][cur_x]+1;
                if(A[ny][nx]==1){
                    return dist[ny][nx];
                }
                q.push(make_pair(ny,nx));
            }
        }
    }

    return -1;
}

int main(){

    cin >> H >> W;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> A[i][j];
        }
    }


    int max_dist = 0;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if(A[i][j] == 0){
                int dist = calc_dist(i,j);
                max_dist = (dist>max_dist) ? dist : max_dist;
            }
        }
    }

    cout << max_dist <<"\n";







    return 0;
}