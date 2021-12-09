//#include <iostream>
//#include <queue>
//#include <algorithm>
//#include <vector>
//using namespace std;
//
//int N, K ,S;
//int y, x;
//
//int visited[201][201] = {};
//int map[201][201] = {};
//int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
//
//int isInside(int y, int x) {
//	if (y<1 || y>N || x<1 || x>N) return 0;
//	return 1;
//}
//struct Node {
//	int y, x;
//	int num;
//	int sec = 0;
//};
//
//vector<Node> vec;
//
//int cmp(Node front, Node back) {
//
//	if (front.num == back.num) {
//		if (front.y == back.y) return front.x < back.x;
//		return front.y < back.y;
//	}
//	else 
//		return front.num < back.num;
//	
//}
//
//int main() {
//
//	queue<Node> que;
//	ios::sync_with_stdio(false);
//	cin.tie(NULL);
//	cout.tie(NULL);
//
//	cin >> N >> K;
//
//	for (int i = 1; i <= N; i++) {
//		for (int j = 1; j <= N; j++) {
//			cin >> map[i][j];
//			if (map[i][j] != 0) {
//				vec.push_back({ i,j,map[i][j],0 });
//				visited[i][j] = 1;
//			}
//		}
//	}
//	cin >> S >> y >> x;
//
//	sort(vec.begin(), vec.end(), cmp);
//
//	int n = vec.size();
//
//	for (int i = 0; i < n; i++) {
//		que.push({ vec[i].y,vec[i].x,vec[i].num,vec[i].sec });
//	}
//
//	int chk_sec = 0;
//	if (S == 0) {
//		cout << 0 << endl;
//		return 0;
//	}
//	while (++chk_sec) {
//		vec.clear();
//		while (!que.empty()) {
//			int cur_y = que.front().y;
//			int cur_x = que.front().x;
//			int cur_sec = que.front().sec;
//			que.pop();
//
//			if (cur_sec == chk_sec) continue;
//
//			for (int i = 0; i < 4; i++) {
//				int ny = cur_y + dir[i][0];
//				int nx = cur_x + dir[i][1];
//
//				if (!isInside(ny, nx) || visited[ny][nx] != 0 || map[ny][nx] != 0) continue;
//
//				map[ny][nx] = map[cur_y][cur_x];
//				visited[ny][nx] = 1;
//				vec.push_back({ ny,nx,map[ny][nx],cur_sec + 1 });
//				que.push({ ny,nx,map[ny][nx],cur_sec + 1 });
//			}
//		}
//
//		if (vec.size() > 0) {
//			sort(vec.begin(), vec.end(), cmp);
//
//			int n = vec.size();
//
//			for (int i = 0; i < n; i++) {
//				que.push({ vec[i].y,vec[i].x,vec[i].num,vec[i].sec });
//			}
//		}
//
//		if (chk_sec == S) break;
//	}
//
//	cout << map[y][x] << endl;
//
//	return 0;
//}