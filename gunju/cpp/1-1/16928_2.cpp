#include<iostream>
#include <vector>
#include <memory.h>
#include <queue>

using namespace std;

int dist[101];
int sc[101];

int main() {
    memset(dist, -1, sizeof(dist));

    int n, m;
    cin >> n >> m;


    int x,y;
    for (int i=0; i< n+m; i++){
        cin >> x >> y;
        sc[x] = y;
    }

    queue<int> q;
    q.push(1);

    while(!q.empty()){
        int cur = q.front();
        q.pop();
        if(cur== 100){
            cout << dist[cur]+1 <<"\n";
            break;
        }

        for (int i=1; i <= 6; ++i){
            if(sc[cur+i]!=0 && dist[sc[cur+i]]==-1){
                q.push(sc[cur+i]);
                dist[sc[cur+i]] = dist[cur]+1;

            }
            if(sc[cur+i]==0 && dist[cur+i]==-1 && cur+i <101){
                q.push(cur+i);
                dist[cur+i] = dist[cur]+1;
            }
        }
    }


    return 0;
}