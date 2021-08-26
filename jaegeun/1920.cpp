// 수 찾기
// https://www.acmicpc.net/problem/1920

#include <iostream>
#include <algorithm>
#include <vector>

#define endl '\n'

using namespace std;

int main()
{
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	freopen_s(new FILE*, "text.txt", "r", stdin);

	int n; cin >> n;

	vector<int> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];

	sort(A.begin(), A.end());

	int m; cin >> m;
	for (int i = 0; i < m; i++)
	{
		int num; cin >> num;
		cout << binary_search(A.begin(), A.end(), num) << endl;
	}
	return 0;
}