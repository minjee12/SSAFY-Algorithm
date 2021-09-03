#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

int n;
vector<long long int> v;
long long int mini = 2000000000;
bool compare(long long int a, long long int b) {
	return abs(a) < abs(b);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//time_t start = clock();
	long long int ret1, ret2;
	cin >> n;
	for (int i = 0; i < n; i++) {
		long long int a;
		cin >> a;
		v.push_back(a);
	}
	sort(v.begin(), v.end(), compare);
	for (int i = 0; i < n-1; i++) {

		if (abs(v[i] + v[i + 1]) < abs(mini)) {
			mini = v[i] + v[i + 1];
			ret1 = v[i];
			ret2 = v[i+1];
		}
	}
	cout << min(ret1, ret2) << " " << max(ret1, ret2);
	//cout << (int)(clock() - start);
	return 0;
}