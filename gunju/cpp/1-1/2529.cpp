#include <iostream>
#include <vector>

using namespace std;

bool check[10];

bool find_max = false;
bool find_min = false;


void go(int idx, int prev, vector<char> &A, string s, bool minmax){
    if(minmax && !find_max) { // max
        if(s.size() == A.size()+1){
            cout << s << "\n";
            find_max= true;
            return;
        }
    }

    if(!minmax && !find_min) { // max
        if(s.size() == A.size()+1){
            cout << s << "\n";
            find_min= true;
            return;
        }
    }
    if(!minmax){
        for (int i=0; i < 10; ++i){
            if(A[idx]=='<'){
                if(prev < i && !check[i]){
                    check[i] = true;
                    go(idx+1, i , A, s+(char)('0'+i), minmax);
                    check[i] = false;
                }
            }
            else{
                if(prev > i && !check[i]){
                    check[i] = true;
                    go(idx+1, i , A, s+(char)('0'+i), minmax);
                    check[i] = false;
                }
            }
        }
    }
    else{
        for (int i=9; i >=0 ; --i){
            if(A[idx]=='<'){
                if(prev < i && !check[i]){
                    check[i] = true;
                    go(idx+1, i , A, s+(char)('0'+i), minmax);
                    check[i] = false;
                }
            }
            else{
                if(prev > i && !check[i]){
                    check[i] = true;
                    go(idx+1, i , A, s+(char)('0'+i), minmax);
                    check[i] = false;
                }
            }
        }
    }

    return;
}

int main(){

    int k;
    cin >> k;

    vector<char> A(k);

    for (int i=0; i<k; ++i){
        cin >> A[i];
    }

    // MAX
    for (int i=9; i>=0; --i){
        check[i]= true;
        go(0, i,A, to_string(i),true);
        check[i] = false;
        if(find_max) break;
    }
    // MIN
    for (int i=0; i<10; ++i){
        check[i]= true;
        go(0, i,A, to_string(i),false);
        check[i] = false;
        if(find_min) break;
    }
    return 0;
}
