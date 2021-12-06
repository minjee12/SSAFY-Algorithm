#include <iostream>
#include <string>
using namespace std;

int n, m;
string s;

int main()
{
	cin >> n >> m;
	cin >> s;

	int res = 0;
	for (int i = 0; i < m; i++){
		//k : O°³¼ö
		int k = 0;
		if (s[i] == 'I'){
			while (s[i + 1] == 'O' && s[i + 2] == 'I'){
				k++;
				if (k == n){
					k--;
					res++;
				}
				i += 2;
			}
			k = 0;
		}
	}
	cout << res;

	return 0;
}