#include <iostream>
#include <string.h>
using namespace std;

char str[31];
int score_list[30];

char left_ghalho[3] = "([";
int score[2] = { 2, 3 };

int ghalho(char* pstr) {
	int type = 0;
	if (*pstr == ')') type = 0;
	else if (*pstr == ']') type = 1;

	char ex = *(pstr - 1);
	int idx = pstr - str;

	if (ex == left_ghalho[type]) {
		//seed
		score_list[idx] = score[type];
		score_list[idx - 1] = -1;
	}
	else if (ex == ')' || ex == ']') {
		for (int i = idx - 2; i >= 0; i--) {
			if (score_list[i] != 0) continue;

			if (str[i] == left_ghalho[type]) {
				score_list[i] = -1;
				score_list[idx] = -1;
				for (int j = i + 1; j <= idx - 1; j++) {
					if (score_list[j] != 0 && score_list[j] != -1) {
						score_list[j] *= score[type];
					}
				}
				break;
			}
		}
	}
	else if (ex == left_ghalho[1 - type]) return 0;
	return 1;
}

int sum() {
	int total = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (score_list[i] == 0) return 0;
		if (score_list[i] != -1) total += score_list[i];
	}
	return total;
}

int calculate() {
	int score = 0;
	char* pstr1 = strchr(str, ')');
	char* pstr2 = strchr(str, ']');
	int button = 0;

	while (1) {
		if (pstr1 == NULL) pstr1 = str + 100;
		if (pstr2 == NULL) pstr2 = str + 100;
		if (pstr1 == pstr2) break;

		char* pstr;
		if (pstr1 < pstr2) {
			pstr = pstr1;
			button = 1;
		}
		else {
			pstr = pstr2;
			button = 2;
		}
		
		if (!ghalho(pstr)) return 0;

		if (button == 1) pstr1 = strchr(pstr1 + 1, ')');
		else pstr2 = strchr(pstr2 + 1, ']');
	}

	score = sum();

	return score;
}

int main() {
	cin >> str;

	cout << calculate();

	return 0;
}