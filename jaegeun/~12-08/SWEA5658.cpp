// 보물상자 비밀번호

#define ULL unsigned long long

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

int N, K;

deque<char> dial;

int get_hex(char c) {
	if (c == 'F') return 15;
	if (c == 'E') return 14;
	if (c == 'D') return 13;
	if (c == 'C') return 12;
	if (c == 'B') return 11;
	if (c == 'A') return 10;
	return (int)(c - '0');
}

void add_num(vector<ULL>& container) {
	int unit = N / 4;
	
	for (int i = 0; i < 4; i++) {
		ULL num = 0;
		for (int j = 0; j < unit; j++) {
			int h = get_hex(dial[i * unit + j]);
			num = (num | h);
			if (j < unit - 1) num = num << 4;
		}
		bool flag = true;
		for (int j = 0; j < container.size(); j++) {
			if (container[j] == num) {
				flag = false;
				break;
			}
		}
		if (flag) container.push_back(num);
	}
}

void rotate_dial() {
	dial.push_front(dial.back());
	dial.pop_back();
}

int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int T; cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> K;
		dial.clear();
		for (int i = 0; i < N; i++) {
			char c; cin >> c;
			dial.push_back(c);
		}
		vector<ULL> nums;
		add_num(nums);
		for (int i = 0; i < N / 4 - 1; i++) {
			rotate_dial();
			add_num(nums);
		}
		sort(nums.begin(), nums.end(), greater<int>());
		cout << "#"<< t + 1<< " " << nums[K - 1] << "\n";
	}
}