#include <iostream>
#include <vector>
#include <cstring>

//#define PRINT

using namespace std;

int dx[] = {-1,-1,0,1,1,1,0,-1};
int dy[] = {0,-1,-1,-1,0,1,1,1};


// 초기 구름 위치 : (N,1) (N,2) (N-1,1) (N-1,2)


struct move_t{
    int d,s;
} marr[100];

int Water[50][50];
bool check[50][50];
int N, M;

#ifdef PRINT
void print_clouds(vector<pair<int,int> > &vect){

    for (int i=0; i< vect.size(); ++i){
        cout << vect[i].first <<" , " << vect[i].second <<"\n";
    }
    return;
}

void print_water(){
    cout <<"\n";
    for (int i=0; i<N; ++i){
        for (int j=0; j<N; ++j){
            cout << Water[i][j] <<" ";
            
        }
        cout <<"\n";
    }
    return;
}
#endif


void add_new_clouds(vector<pair<int,int> > &c_vect){
    //check == true 였던 곳은 건너뛰고 false로 돌려야함!

    for (int i=0; i< N; ++i){
        for (int j=0; j< N; ++j){
            if(check[i][j]) continue;
            
            if(!check[i][j] && Water[i][j] >=2){
                c_vect.push_back(make_pair(i,j));
                Water[i][j]-=2;
                
            }
        }
    }

    fill(&check[0][0] , &check[0][0]+2500, false);

    return;
}


// 재귀로 구현?
void move_clouds(int m_idx, vector<pair<int,int> > &c_vect){
    if(m_idx == M) return;
    move_t cur_m = marr[m_idx];

    int ny, nx;

#ifdef PRINT
    print_water();
    print_clouds(c_vect);
#endif

    for (int i=0; i< c_vect.size(); ++i){
        
        ny = c_vect[i].first + (cur_m.s * dy[cur_m.d-1])%N;
        ny = (N+ ny%N)%N;
        nx = c_vect[i].second + (cur_m.s * dx[cur_m.d-1])%N;
        nx = (N+ nx%N)%N;
#ifdef PRINT
        cout << "(" << ny <<", " <<nx <<")\n";
#endif
        Water[ny][nx]++;
        check[ny][nx] = true;

        c_vect[i].first = ny;
        c_vect[i].second = nx;

    }
    // 구름이 사라졌다! 

    //cnt : 물복사용 임시배열
    // 모든 구름이 사라진 후 물복사 버그 시작
    for (int i=0; i< c_vect.size(); ++i){
        int cnt =0;
        // 대각선 4방향
        for (int k=1; k<8; k+=2){
            ny = c_vect[i].first + dy[k];
            nx = c_vect[i].second + dx[k];
            if(ny <0 || ny >= N || nx <0 || nx >=N) continue;
            if(Water[ny][nx]>0) cnt++;
            
        }
        Water[c_vect[i].first][c_vect[i].second] += cnt;
    }

    // 새 구름으로 재귀 탐색
    c_vect.clear();

    add_new_clouds(c_vect);
    move_clouds(m_idx+1, c_vect);

    return;
}

// 이동이 끝났다 ? == 구름이 생겨서 각 칸에 -2가 적용된 후!
int sum_water(){
    int res =0;
    for (int i=0; i< N; ++i){
        for (int j=0; j <N; ++j){
            res+= Water[i][j];
        }
    }

    return res;
}


int main(){
    cin >> N >>M;

    for (int i=0; i< N; ++i){
        for (int j=0; j< N; ++j){
            cin >> Water[i][j];
        }
    }
    for (int i=0; i<M ;++i){
        cin >> marr[i].d >> marr[i].s;
    }

    // init
    vector<pair<int,int> > c_vect;

    c_vect.push_back(make_pair(N-2,0));
    c_vect.push_back(make_pair(N-2,1));
    c_vect.push_back(make_pair(N-1,0));
    c_vect.push_back(make_pair(N-1,1));
    
    move_clouds(0, c_vect);
    
    int ans = sum_water();

    cout << ans <<"\n";

    return 0;
}