#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

char arr[9];
vector<int> v;

bool valid(int a, vector<int> &v) {
	for (int i = 0; i < a; i++) {
		if (arr[i] == '>' && v[i] < v[i + 1])
			return false;

		else if (arr[i] == '<' && v[i] > v[i + 1])
			return false;
	}
	return true;
}

void max(int a) {
	for (int i = 0; i < a + 1; i++) {
		v.push_back(9 - i);
	}
	while (true) {
		if (valid(a, v)) break;
		prev_permutation(v.begin(), v.end()); //
	}
	for (int i = 0; i < v.size(); i++) {
		cout << v[i];
	}
}

void min(int a) {
	for (int i = 0; i < a + 1; i++) {
		v.push_back(i);
	}
	while (true) {
		if (valid(a, v)) break;
		next_permutation(v.begin(), v.end());
	}
	for (int i = 0; i < v.size(); i++) {
		cout << v[i];
	}
}

int main() {
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> arr[i];
	}
	max(k);
	v.clear();
	cout << "\n";
	min(k);

	return 0;
}