#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// For Memoization (0: 가로,1: 세로,2 : 대각)
int Memo[16][16][3]; 



int main(){
    int N;
    cin >> N;

    // 메모 초기화
    fill(&Memo[0][0][0], &Memo[0][0][0] +768, 0 );

    vector<vector<int> > House(N,vector<int>(N,0));

    for (int i=0; i<N; ++i){
        for (int j=0; j<N; ++j){
            cin >> House[i][j];
        }
    }

    // 첫 파이프 
    Memo[0][1][0] = 1; // 
    
    
    // Memo 채워 나가기 (열 0,1 인경우는 제외)
    for (int i=0; i<N; i++){
        for (int j=2; j<N; j++){
            // 이전 가로
            if(House[i][j]!=1){
                Memo[i][j][0] += (Memo[i][j-1][0] + Memo[i][j-1][2]); // 가로 + 대각
            }
            // 이전 세로
            if(House[i][j]!=1 && i>0){
                Memo[i][j][1] += (Memo[i-1][j][1] + Memo[i-1][j][2]);
            }
            // 이전 대각
            if(i >0 && House[i-1][j]!=1 && House[i][j-1]!=1 && House[i][j]!=1){
                Memo[i][j][2] += (Memo[i-1][j-1][0]+Memo[i-1][j-1][1]+Memo[i-1][j-1][2]);
            }
        }
    }

    int ans = (Memo[N-1][N-1][0]+Memo[N-1][N-1][1]+Memo[N-1][N-1][2]);

    cout << ans <<"\n";


    return 0;
}