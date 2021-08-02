#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[11]; // ����
int path[4]; // �� �������� ����
int res[11]; // �� lev������ �������갪
int maxi = -1000000001, mini = 1000000001;

int cal(int a, int b, int num) {
	for (int i = 0; i < 4; i++) {
		if (num == 0)
			return a + b;
		else if (num == 1)
			return a - b;
		else if (num == 2)
			return a * b;
		else if (num == 3)
			return a / b;
	}
}

void run(int start) {
	if (start == n - 1) {
		maxi = max(maxi, res[start]);
		mini = min(mini, res[start]);
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (path[i] == 0) continue;
		res[start + 1] = cal(res[start], arr[start + 1], i);
		path[i]--;
		run(start + 1);
		path[i]++;
		res[start + 1] = 0;
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	for (int i = 0; i < 4; i++) {
		cin >> path[i];
	}
	res[0] = arr[0];
	run(0);
	cout << maxi << "\n";
	cout << mini << "\n";

	return 0;
}

//string�� +�� ���� ���ڿ� ���ϼ��� ������ -�� �ȵ�
//path -> index: level
//used -> index: x(���° branch�ΰ�)