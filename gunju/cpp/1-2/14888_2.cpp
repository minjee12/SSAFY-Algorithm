#include <vector>
#include <iostream>

using namespace std;

int N;
int nums[12];

int ops[4];

vector<int> candidates;

void go(int idx, int res){
    if(idx == N){
        candidates.push_back(res);
        return;
    }

    for (int i=0; i< 4; ++i){
        if(ops[i]>0){
            ops[i]= ops[i]-1;
            if(i==0){ // +
                go(idx+1, res = res+ nums[idx]);
            }
            if(i==1){ // -
                go(idx+1, res = res - nums[idx]);
            }
            if(i==2){ // *
                go(idx+1, res = res * nums[idx]);
            }
            if(i==3){ // /
                go(idx+1, res = (int)(res/ nums[idx]));
            }
            ops[i]= ops[i]+1;
        }
    }
    return;
}


int main(){

    cin >> N;
    for (int i=0; i<N; ++i){
        cin >> nums[i];
    }

    for (int i=0; i<4; ++i){
        cin >> ops[i];
    }

    go(1, nums[0]);

    cout << *max_element(candidates.begin(), candidates.end()) << "\n";
    cout << *min_element(candidates.begin(), candidates.end()) << "\n";

    return 0;
}