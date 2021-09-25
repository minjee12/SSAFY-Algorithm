// UCPC는 무엇의 약자일까?
// https://www.acmicpc.net/problem/15904

#include <iostream>
#include <string>
using namespace std;

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	string str; getline(cin, str);
	string result;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == 'U' && result.length() == 0)
			result += str[i];
		if (str[i] == 'C' && result.length() == 1)
			result += str[i];
		if (str[i] == 'P' && result.length() == 2)
			result += str[i];
		if (str[i] == 'C' && result.length() == 3) {
			result += str[i];
			cout << "I love UCPC";
			return 0;
		}
	}
	cout << "I hate UCPC";
	return 0;
}