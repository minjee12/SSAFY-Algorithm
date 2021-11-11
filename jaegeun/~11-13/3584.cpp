// 가장 가까운 공통 조상
// https://www.acmicpc.net/problem/3584

#include <iostream>
#include <cstring>
#include <vector>
#define MAX 10001

using namespace std;

int p[MAX];


int main() {
	freopen_s(new FILE*, "text.txt", "r", stdin);

	int T; cin >> T;
	for (int t = 0; t < T; t++) {
		memset(p, 0, sizeof(p));
		int N; cin >> N;
		for (int i = 0; i < N - 1; i++) {
			int A, B; cin >> A >> B;
			p[B] = A;
		}
		int fA, fB; cin >> fA >> fB;

		// 루트가 입력으로 들어온 경우
		if (p[fA] == 0) {
			cout << fA << "\n";
			continue;
		}
		if (p[fB] == 0) {
			cout << fB << "\n";
			continue;
		}

		vector<int> pfA; // fA의 부모들
		pfA.push_back(fA); // 자기 자신 추가
		int parent_A = p[fA];
		while (parent_A != 0) {
			pfA.push_back(parent_A);
			parent_A = p[parent_A];
		}

		int parent_B = p[fB];

#ifdef _DEBUG
		cout << "부모들 : ";
		for (auto x : pfA) {
			cout << x << " ";
		}
		cout << "\n";
#endif
		int answer = 0;
		while (parent_B != 0) {
			for (int idx = 0; idx < pfA.size(); idx++) {
				if (pfA[idx] == parent_B) {
					answer = parent_B;
					break;
				}
			}
			if (answer != 0) break;
			parent_B = p[parent_B];
		}

		cout << answer << "\n";
	}
	return 0;
}