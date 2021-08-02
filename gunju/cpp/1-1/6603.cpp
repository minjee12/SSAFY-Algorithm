#include <iostream>
#include <vector>
#include <memory.h>


using namespace std;

bool check[50];

void go(vector<int> &A, int idx, int cnt, string tmp){

    if(idx > A.size()) return;

    if(cnt == 6){
        cout << tmp << "\n";
        return;
    }

    if(!check[A[idx]]){
        check[A[idx]]= true;
        go(A, idx+1, cnt+1, tmp+to_string(A[idx])+' ');
        check[A[idx]] = false;
        go(A, idx+1, cnt, tmp);
    }
    return;

}

int main(){

    int n;
    while(true){
        cin >> n; 
        vector<int> A(n);
        memset(check,false,sizeof(check));

        for (int i=0; i< n;i++){
            cin >> A[i];
        }
    
        go(A, 0,0,"");
        cout <<"\n";

    }

    return 0;
}