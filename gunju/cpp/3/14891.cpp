#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


int main() {
    // 톱니바퀴 : idx 0 = 12시
    vector<string > A(4);
    for (int i=0 ;i <4 ; ++i){
        cin >>A[i];
    }

    int n;
    int idx, dir;
    cin >> n;

    for (int i=0; i< n; ++i){
        cin >> idx >> dir;
        //유효 인덱스 : 2 , 6

        vector<int> d(4,0); // 방향벡터 초기화
        
        d[idx-1] = dir;

        // 기준 대비 왼쪽

        for(int left = idx-2; left >=0; --left){
            if(A[left][2] != A[left+1][6]){
                d[left] =  -d[left+1];
            }
            else { // 회전 안함 (break) ==> 나머지 d =0
                break;
            }
        }

        // 기준 대비 오른쪽
        for(int right = idx; right < 4; ++right){
            if(A[right][6] != A[right-1][2]){
                d[right] =  -d[right-1];
            }
            else {
                break;
            }
        }

        // 각 회전 방향에 따라 회전
        for(int i=0 ; i< 4; ++i){
            if(d[i] == 1){ // 시계 (rotate right)
                rotate(A[i].rbegin(), A[i].rbegin()+1, A[i].rend());
            }
            if(d[i] == -1){
                rotate(A[i].begin(), A[i].begin()+1 , A[i].end());
            }
            if(d[i] == 0) continue;
        }
    }
    
    int ans = 0;
    for (int i= 0; i< 4; ++i){
        int tmp =1;
        for (int j= 1; j<=i; ++j){
            tmp*=2;
        }
        if(A[i][0] == '1'){
            ans += tmp;
        }
        
        cout << A[i] <<"\n";
    }
    
    cout << ans << "\n";

    return 0;
}