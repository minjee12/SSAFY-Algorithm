// 컨베이어 벨트 위의 로봇
// https://www.acmicpc.net/problem/20055

#include <iostream>
#include <queue>

using namespace std;

// 벨트 길이, 내구도 개수
int N, K; 

deque<pair<int, bool>> up_belt;
deque<pair<int, bool>> down_belt;

void rotate_belt()
{
	down_belt.push_back(up_belt.back());
	up_belt.pop_back();
	up_belt.push_front(down_belt.front());
	down_belt.pop_front();
}

void move_robot()
{
	for(int i = N - 1; i > 0; i--) {
		if (up_belt[i - 1].second && up_belt[i].first >= 1 && !up_belt[i].second) {
			up_belt[i].first--;
			up_belt[i].second = true;
			up_belt[i - 1].second = false;
		}
		if (i == N - 1) up_belt[i].second = false; //로봇 내림
	}
}

bool check_durability() {
	int d_cnt = 0;
	for (int i = 0; i < N; i++) {
		if (up_belt[i].first == 0) d_cnt++;
	}
	for (int i = 0; i < N; i++) {
		if (down_belt[i].first == 0) d_cnt++;
	}
	if (d_cnt >= K) return true;
	return false;
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	
	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		int d; cin >> d;
		up_belt.push_back({ d, false });
	}
	for (int i = 0; i < N; i++) {
		int d; cin >> d;
		down_belt.push_front({ d, false });
	}

	int cnt = 1;
	while (true) {
		rotate_belt();
		up_belt[N - 1].second = false; // 로봇 내림
		move_robot();
		// 내구도가 0이 아니면 로봇 올림
		if (up_belt[0].first > 0) {
			up_belt[0].second = true;
			up_belt[0].first--;
		}
		
		if (check_durability()) break;
		cnt++;
	}
	cout << cnt;
	return 0;
}