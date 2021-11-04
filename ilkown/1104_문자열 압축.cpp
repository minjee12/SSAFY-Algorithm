#include <vector>
#include <string>
#include <iostream>
using namespace std;

int solution(string s) {
	
	int answer = 999999;

	int len = s.length();

	for (int i = 1; i <= len; i++) {
		string temp = "";
		for (int j = 0; j < len;) {
			int cnt = 1;
			string words = "";
			int cant = 0;
			for (int k = j; k < j + i; k++) {
				if (k >= len) {
					cant = 1;
					break;
				}
				words += s[k];
			}
			j += i;
			if (cant) {
				temp += words;
				break;
			}
			int a = j;

			while (words == s.substr(a, i)) {
				a += i;
				cnt++;
			}
			if (cnt == 0 || cnt == 1) {
				if (j + i >= len) {
					temp += words + s.substr(j, len - j);
					break;
				}
				temp += words;
			}
			else {
				if (j + i >= len) {
					temp += to_string(cnt) + words;
					temp += s.substr(a, len - a);
					break;
				}
				temp += to_string(cnt) + words;
				j = a;
			}
		}
		if (answer > temp.length() && temp.length()>=1) answer = temp.length();
	}

	return answer;
}

int main() {

	string s = "xxxxxxxxxxyyy";
	cout << solution(s) << endl;


	return 0;
}