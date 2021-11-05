#include <iostream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;

char str[1001];

int scale(int cnt) {
	if (1 < cnt && cnt < 10) return 1;
	else if (10 <= cnt && cnt < 100) return 2;
	else if (1000 <= cnt) return 3;
	return 0;
}

int solution(string s) {
	int answer = 0;
	int s_size = s.size();
	memcpy(str, &s[0], s_size);
	str[s_size] = '\0';

	int mini = s_size;
	char now[501] = { 0 };
	char ex[501] = { 0 };

	for (int size = 1; size <= (s_size + 1) / 2; size++) {
		int index;
		int len = 0;
		int cnt = 1;
		for (index = 0; index < s_size ; index += size) {
			memcpy(now, str + index, size);
			now[size] = '\0';

			if (index == 0) {
				memcpy(ex, now, size + 1);
				continue;
			}

			if (!strcmp(now, ex)) {
				cnt++;
			}
			else {
				len += size;
				len += scale(cnt);
				cnt = 1;
			}

			memcpy(ex, now, size + 1);
			if (index + size > s_size - 1) {
				len += s_size - index;
				break;
			}
		}
		len += scale(cnt);
		if (s_size == 1) len = 1;
		mini = (len < mini) ? len : mini;
	}
	answer = mini;
	return answer;
}

int main() {
	string s;
	cin >> s;

	cout << solution(s);

	return 0;
}