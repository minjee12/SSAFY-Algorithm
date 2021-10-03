#include <iostream>
#include <string>
#include <vector>

using namespace std;

int row, col;

int room[50][50] = {0};

int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};

int answer =0;

void search(int rx, int ry, int d){
    if(room[ry][rx]==0){
        room[ry][rx] = -1; // clean finish
        answer++;
    }
    
    int nx, ny;
    
    bool back= true;
    int idx = (d+3)%4;
    for(int i=0; i<4; i++, idx = (idx+3)%4){
		printf("%d\n",idx);
        ny = ry+dy[idx];
        nx = rx+dx[idx];
        if(room[ny][nx]==0){
            search(nx,ny,idx);
            back=false;
            break;
        }
    }
    
    if(back){
        ny = ry+dy[(d+2)%4];
        nx = rx+dx[(d+2)%4];
        if(room[ny][nx]==1) 
            return;
        else 
            search(nx, ny, d);
    }
    
    return;
}

int main() {
    cin >> row >> col;
    
    int rx, ry, d;
    
    cin >> ry >> rx >> d;
    
    for (int i=0; i< row; i++ ){
        for(int j=0; j<col; j++){
            cin >> room[i][j];
        }
    }
    
    search(rx, ry, d);
    
    cout<< answer <<endl;
    
    return 0;
}
