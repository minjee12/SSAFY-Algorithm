#include <iostream>
#include <string.h>

#define size 1000

using namespace std;

int n, m;
int mul[size] = { 1 };
int len = 1;

void gophagi() {
	for (int i = 0; i < m; i++) // m�� ����
	{
		for (int j = 0; j < len; j++) {
			mul[j] *= n - i; // �� �ε���(j)�� (n-i)�� ����
		}
		
		int num = mul[0];
		for (int j = 0; j <= len + 2; j++) {
			int now = num % 10; // ���� �ε����� �� ����
			mul[j] = now;
			int next = num / 10 + mul[j + 1]; // ���� �ڸ����� �ش��ϴ� ����
			// ���� �ڸ������� �ִ�� ���� �� �� �ִ� �ڸ����� '+ 2' (0 ~ 999)
			num = next;
		}
		len += 2;
	}
}

void nanugi() {
	for (int i = m; i >= 1; i--) // m�� ����
	{
		int num = mul[len];

		for (int j = len; j >= 0; j--) {
			int now = num / i;			//���� �ε����� �� ����
			mul[j] = now;
			if (j == 0) break;
			int next = (num % i) * 10 + mul[j - 1]; // ���� �ڸ����� �ش��ϴ� ����
			num = next;
		}
	}
}

void output() { // �ڸ����� ���������� ��Ȯ�ϰ� �����ص��� �ʾƼ� ���� �Լ�
	int flg = 1;
	for (int i = len; i >= 0; i--) {
		if (mul[i] == 0 && flg == 1) continue; // ������� �� �ִ� �ڸ��� �� �ִ� ������ ���� -> 0�� �ȳ����� �����ϴ� ������ ��¥ �ִ� �ڸ���
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