#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> conveior;
vector<int> robot;
int N, K;
int cnt;
int cnt_delete = 0;
int cnt_robot = 0;

void delete_robot() {
	for (int i = 0; i < cnt_delete; i++) {
		cnt_robot--;
		robot.erase(robot.begin());
	}
	cnt_delete = 0;
}

int solution() {
	int step = 0;

	while (1) {
		step++;
		//1. ��Ʈ ȸ��
		int tmp = conveior.back();
		conveior.pop_back();
		conveior.insert(conveior.begin(), tmp);
		//   �����̾� ȸ������ �κ� ��ġ + 1
		for (int n = 0; n < cnt_robot; n++) {
			robot[n]++;
			if (robot[n] >= N - 1) cnt_delete++;
		}
		delete_robot();

		//2. �κ� �̵�
		for (int n = 0; n < cnt_robot; n++) {
			if (conveior[robot[n] + 1] == 0) continue;
			if (n > 0 && (robot[n - 1] == robot[n] + 1)) continue;

			robot[n]++;
			if (robot[n] >= N - 1) cnt_delete++;

			int life = --conveior[robot[n]]; // �����̾� ���� - 1
			if (life == 0) {
				cnt++; // �����̾� ���� 0�̸� ���� + 1
				if (cnt == K) return step; // ���� == K�� ����
			}
		}
		delete_robot();

		//3. �κ� �߰�
		if (conveior[0] != 0) {
			cnt_robot++;
			robot.push_back(0);
			conveior[0]--;
			//4. bye
			if (conveior[0] == 0) {
				cnt++; // �����̾� ���� 0�̸� ���� + 1
				if (cnt == K) return step; // ���� == K�� ����
			}
		}
	}
}

int main() {
	cin >> N >> K;

	for (int i = 0; i < 2 * N; i++) {
		int life;
		cin >> life;
		conveior.push_back(life);
	}

	cout << solution();

	return 0;
}