#include <iostream>
#include <string.h>

#define size 1000

using namespace std;

int n, m;
int mul[size] = { 1 };
int len = 1;

void gophagi() {
	for (int i = 0; i < m; i++) // m번 시행
	{
		for (int j = 0; j < len; j++) {
			mul[j] *= n - i; // 각 인덱스(j)에 (n-i)씩 곱함
		}
		
		int num = mul[0];
		for (int j = 0; j <= len + 2; j++) {
			int now = num % 10; // 현재 인덱스에 들어갈 숫자
			mul[j] = now;
			int next = num / 10 + mul[j + 1]; // 다음 자리수에 해당하는 숫자
			// 현재 자리수에서 최대로 증가 할 수 있는 자리수는 '+ 2' (0 ~ 999)
			num = next;
		}
		len += 2;
	}
}

void nanugi() {
	for (int i = m; i >= 1; i--) // m번 시행
	{
		int num = mul[len];

		for (int j = len; j >= 0; j--) {
			int now = num / i;			//현재 인덱스에 들어갈 숫자
			mul[j] = now;
			if (j == 0) break;
			int next = (num % i) * 10 + mul[j - 1]; // 이전 자리수에 해당하는 숫자
			num = next;
		}
	}
}

void output() { // 자리수가 어디까지인지 정확하게 저장해두지 않아서 만든 함수
	int flg = 1;
	for (int i = len; i >= 0; i--) {
		if (mul[i] == 0 && flg == 1) continue; // 만들어질 수 있는 자리수 중 최대 값에서 시작 -> 0이 안나오기 시작하는 순간이 진짜 최대 자리수
		else {
			flg = 0;
			cout << mul[i];
		}
	}
}

int main() {
	cin >> n >> m;
	if (m > n - m) m = n - m;

	gophagi();

	nanugi();

	output();

	return 0;
}