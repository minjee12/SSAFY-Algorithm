#include<iostream>
#include<vector>

using namespace std;

typedef struct {
	int i, num;
} D;
int N;
vector<D> v;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		v.push_back({i+1, a});
	}
	int n = 0; //현재 인덱스
	int len = N;
	for (int i = 0; i < N; i++) {
		cout << v[n].i << " ";
		int m = v[n].num;
		if (m > 0) m--;

		v.erase(v.begin() + n);
		n += m;
		len--;
		if (len == 0) break;

		if (n < 0) n = len + n % len;
		n %= len;

	}

	return 0;
}