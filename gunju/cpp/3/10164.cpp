#include <iostream>
#include <vector>

using namespace std;


int N , M, K;

int calc_path(int h, int w){

    vector< vector<int> > D(h, vector<int>(w,1));

    for (int y=1; y<h; ++y){
        for (int x=1; x<w; ++x){
            D[y][x] = D[y][x-1] + D[y-1][x];
        }
    }
    return D[h-1][w-1];
}





int main(){
    cin >> N >> M >> K;

    int ans;

    if(K >0){
        int kx = (K-1)%M; // 2
        int ky = (K-1)/M; // 1

        int sx = M - kx;
        int sy = N - ky;

        ans = calc_path(ky+1,kx+1) * calc_path(sy,sx);
    }
    else{
        ans = calc_path(N,M);
    }
    
    cout << ans << "\n";


    return 0;
}