#include <iostream>
#include <vector>
#include <string>
#include <memory.h>

using namespace std;

int R, C;
int N;

char A[200][200];

char B[200][200]; 


int dx[] = {0,0,0,-1,1};
int dy[] = {0,-1,1,0,0};


int main(){
    cin >> R >> C >> N;


    for (int i=0; i <R; ++i){
        for (int j=0; j<C; ++j){
            cin >> A[i][j];
            B[i][j] = 'O';
        }
    }


    if(N%2 ==0 ){
        for (int i=0; i<R; ++i){
            for (int j=0; j<C; ++j){
                cout << B[i][j];
            }
            cout <<"\n";
        }
        return 0;
    }


    for (int n=1; n<N; n+=2){
        memset(B,'O',sizeof(B));
        for (int i=0; i<R; ++i){
            for (int j=0; j<C; ++j){
                if(A[i][j] =='O'){
                    for (int k=0; k<5; ++k){
                        int ny = i + dy[k];
                        int nx = j + dx[k];
                        if(ny <R&& ny >=0 && nx <C && nx >=0){
                            B[ny][nx] = '.';
                        }
                    }
                }
            }
        }
        memcpy(A, B, sizeof(B));
    }

    for (int i=0; i<R; ++i){
        for (int j=0; j<C; ++j){
            cout << A[i][j];
        }
        cout <<"\n";
    }

    return 0;
}