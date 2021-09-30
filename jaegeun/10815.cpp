// 숫자 카드
// https://www.acmicpc.net/problem/10815

#include <iostream>
#include <algorithm>
#define MAX 500000
using namespace std;

int card_sg[MAX];

int main()
{
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> card_sg[i];
	}
	sort(card_sg, card_sg + n);
	int m; cin >> m;
	
	for (int i = 0; i < m; i++) {
		int c; cin >> c;
		if (binary_search(card_sg, card_sg + n, c)) cout << 1 << " ";
		else cout << 0 << " ";
	}
	return 0;
}