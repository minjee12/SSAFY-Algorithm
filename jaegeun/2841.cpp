// 외계인의 기타 연주
// https://www.acmicpc.net/problem/2841

#include <iostream>
#include <queue>

using namespace std;

int N, P;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> N >> P;

	deque<int> guitar[6];

	int finger_cnt = 0;
	while (N--) {
		int line, fret; cin >> line >> fret;
		line--;
		if (guitar[line].size() == 0) { // 손가락 안올림
			guitar[line].push_back(fret);
			finger_cnt++;
		}
		else {
			// 가장 높은 프렛과 비교
			// 1. fret과 같을 때
			if (fret == guitar[line].back()) {
				continue;
			}
			// 2. 기타의 프렛이 멜로디보다 낮을 때
			else if (fret > guitar[line].back()) {
				// 손가락 추가
				guitar[line].push_back(fret);
				finger_cnt++;
			}
			// 3. 기타의 프렛이 멜로디보다 높을 때
			else {
				// 낮거나 같은 음이 나올 때 까지 손가락 떼기
				while (true) {
					if (!guitar[line].size() ||guitar[line].back() <= fret) break;
					guitar[line].pop_back();
					finger_cnt++;
				}
				if (!guitar[line].size()) {
					guitar[line].push_back(fret);
					finger_cnt++;
					
				}
				else if (guitar[line].back() == fret){
					continue;
				}
				else {
					guitar[line].push_back(fret);
					finger_cnt++;
				}
			}
		}
	}
	cout << finger_cnt;
	return 0;
}