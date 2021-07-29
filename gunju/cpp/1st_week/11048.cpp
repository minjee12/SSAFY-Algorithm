#include <iostream>
#include <vector>

using namespace std;

int main(){

    int n, m;
    cin >> n >> m;

    vector<vector<int> > A(n,vector<int>(m));
    vector<vector<int> > D(n,vector<int>(m,0));

    for (int i=0; i < n; ++i){
        for(int j=0; j<m; ++j){
            cin >> A[i][j];
        }
    }


    D[0][0] = A[0][0];
    for (int i=1; i< n; ++i){
        D[i][0]= A[i][0] + D[i-1][0];
    }
    for (int i=1; i< m; ++i){
        D[0][i]= A[0][i] + D[0][i-1];
    }

    for (int i=0; i<n-1; ++i){
        for (int j=0; j<m-1; ++j){
            D[i+1][j+1] = A[i+1][j+1] + max(D[i+1][j] , D[i][j+1]);
        }
    }


    cout << D[n-1][m-1] << "\n";

    return 0;
}

