#include <vector>
#include <iostream>


using namespace std;

int w,h;

int A[500][500];

// 한 점당 23 가지

//[0] ㄱ * 8 (transpose(2) * flip(4))
//[1] N * 8 (transpose(2) * flip(4))
//[2] ㅗ * 4 (16~19) (transpose(2) * flip(2))
//[3] ㅣ * 2 (20~21) (transpose(2))
//[4] ㅁ * 1 (22) (right, down)
int dx[5][4] = {
    {0,1,1,1},
    {0,1,1,2},
    {0,-1,0,1},
    {0,0,0,0},
    {0,0,1,1}
};
int dy[5][4] = {
    {0,0,1,2},
    {0,0,1,1},
    {0,0,1,0},
    {0,1,2,3},
    {0,1,0,1}
};




int flip[4][2] ={{1,1},{1,-1},{-1,1},{-1,-1}};

int ans=0;

int main(){

    cin >> h >> w;
    for (int i=0; i < h; ++i){
        for(int j=0; j<w; ++j){
            cin >> A[i][j];
        }
    }

    // 탐색...
    for (int y=0; y < h; ++y){
        for(int x=0; x<w; ++x){
            int nx, ny;
            int sum, sum1, sum2;
            for(int ty=0; ty<5; ++ty){ // 5type blocks
                if(ty<2){ // 8 cases
                    for(int f=0; f<4; ++f){
                        sum1=0, sum2=0;
                        for(int k=0; k<4; ++k){
                            // loop unrolling (2 transpose)
                            nx = x+ dx[ty][k]*flip[f][0];
                            ny = y+ dy[ty][k]*flip[f][1];
                            if(nx>=0 && nx <w && ny>=0 && ny<h){
                                sum1+= A[ny][nx];
                            }

                            //transpose
                            ny = y+ dx[ty][k]*flip[f][0];
                            nx = x+ dy[ty][k]*flip[f][1];
                            if(nx>=0 && nx <w && ny>=0 && ny<h){
                                sum2+= A[ny][nx];
                            }
                        }

                        ans = max( max(sum1, sum2), ans);
                    }
                }
                if(ty==2){ // ㅗ : 4 cases
                    for(int f=0; f<4; f+=3){ // 2cases
                        sum1=0, sum2=0;
                        for(int k=0; k<4; ++k){
                            // loop unrolling (2 transpose)
                            nx = x+ dx[ty][k]*flip[f][0];
                            ny = y+ dy[ty][k]*flip[f][1];
                            if(nx>=0 && nx <w && ny>=0 && ny<h){
                                sum1+= A[ny][nx];
                            }

                            //transpose
                            ny = y+ dx[ty][k]*flip[f][0];
                            nx = x+ dy[ty][k]*flip[f][1];
                            if(nx>=0 && nx <w && ny>=0 && ny<h){
                                sum2+= A[ny][nx];
                            }
                        }
                        ans = max( max(sum1, sum2), ans);
                    }
                }
                if(ty==3){
                    sum1=0, sum2=0;
                    for(int k=0; k<4; ++k){
                        // loop unrolling (2 transpose)
                        nx = x+ dx[ty][k];
                        ny = y+ dy[ty][k];
                        if(nx>=0 && nx <w && ny>=0 && ny<h){
                            sum1+= A[ny][nx];
                        }

                        //transpose
                        ny = y+ dx[ty][k];
                        nx = x+ dy[ty][k];
                        if(nx>=0 && nx <w && ny>=0 && ny<h){
                            sum2+= A[ny][nx];
                        }
                    }
                    ans = max( max(sum1, sum2), ans);
                }
                if(ty==4){
                    sum=0;
                    for(int k=0; k<4; ++k){
                        nx = x+ dx[ty][k];
                        ny = y+ dy[ty][k];
                        if(nx>=0 && nx <w && ny>=0 && ny<h){
                            sum+= A[ny][nx];
                        }

                    }
                    ans = max(sum, ans);
                }
            }
        }
    }

    cout << ans <<"\n";


    return 0;
}