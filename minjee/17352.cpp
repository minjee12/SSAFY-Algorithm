#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct {
	int a, b;
} D;
vector<D> v;
int arr[300001];
int n;
int findboss(int target) {
	if (arr[target] == 0) return target;
	int boss = findboss(arr[target]);
	arr[target] = boss; // È¿À²¼º
	return boss;
}

void setunion(int a, int b) {
	int aboss = findboss(a);
	int bboss = findboss(b);
	arr[bboss] = aboss;
}

int main() {
	cin >> n;
	for (int i = 0; i < n - 2; i++) {
		int a, b;
		cin >> a >> b;
		v.push_back({ a,b });
	}
	int len = v.size();
	for (int x = 0; x < len; x++) {
		if (findboss(v[x].a) != findboss(v[x].b)) {
			setunion(v[x].a, v[x].b);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (arr[i] == 0) cout << i << " ";
	}

	return 0;
}